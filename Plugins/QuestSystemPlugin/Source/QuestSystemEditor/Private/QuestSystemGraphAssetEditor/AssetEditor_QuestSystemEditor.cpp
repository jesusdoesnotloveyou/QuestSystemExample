// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/AssetEditor_QuestSystemEditor.h"

#include "AITestsCommon.h"
#include "QuestSystemRuntime/Public/QuestSystemGraph.h"
#include "QuestSystemGraphAssetEditor/AssetQuestSystemGraphSchema.h"
#include "QuestSystemGraphAssetEditor/EdGraph_QuestSystemGraph.h"
#include "QuestSystemGraphAssetEditor/AssetQuestEditorToolbar.h"
#include "EdGraphUtilities.h"
#include "Framework/Commands/GenericCommands.h"
#include "GraphEditorActions.h"
#include "QuestSystemGraphAssetEditor/GraphEditorSettings_QuestSystemEditor.h"
#include "ISettingsViewer.h"

#include "HAL/PlatformApplicationMisc.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "EditorStyle/Public/EditorStyleSet.h"

#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdNode_QuestSystemGraphEdge.h"

DEFINE_LOG_CATEGORY_STATIC(LogAssetEditor_QuestSystemGraph, All, All);

#define LOCTEXT_NAMESPACE "QuestSystemEditor"

const FName FAssetEditor_QuestSystemEditor::QuestSystemEditorAppIdentifier( TEXT("QuestSystemEditorApp") );

const FName FAssetEditor_QuestSystemEditor::PropertiesTabId( TEXT ("QuestSystemEditor_Properties" ) );
const FName FAssetEditor_QuestSystemEditor::ViewportTabId( TEXT ("QuestSystemEditor_Viewport" ) );
const FName FAssetEditor_QuestSystemEditor::SettingsTabId( TEXT ("QuestSystemEditor_Settings" ) );

FAssetEditor_QuestSystemEditor::FAssetEditor_QuestSystemEditor()
{
	EditingGraph = nullptr;
    EditorSettings = nullptr;
}

FAssetEditor_QuestSystemEditor::~FAssetEditor_QuestSystemEditor()
{
	EditingGraph = nullptr;
    EditorSettings = nullptr;
	
}

/**
 *TODO : Try to implement test action for Toolbar buttons
 */
void FAssetEditor_QuestSystemEditor::CreateNewNode()
{
    if (!EditingGraph || !EditingGraph->EdGraph) return;
    //EditingGraph->EdGraph->;
}

bool FAssetEditor_QuestSystemEditor::CanCreateNewNode() const
{
    return true;
}

void FAssetEditor_QuestSystemEditor::InitQuestSystemEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UQuestSystemGraph* GraphToEdit)
{
	EditingGraph = GraphToEdit;
    EditorSettings = NewObject<UGraphEditorSettings_QuestSystemEditor>(UGraphEditorSettings_QuestSystemEditor::StaticClass());
	CreateEdGraph();

	FGenericCommands::Register(); // Usually done in StartupModule()
	FGraphEditorCommands::Register();

    if (!ToolbarBuilder.IsValid()) ToolbarBuilder = MakeShareable(new FAssetQuestEditorToolbar(SharedThis(this)));

    TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
    ToolbarBuilder->AddQuestEditorToolbar(ToolbarExtender);

    //~ BindCommands();
    CreateInternalWidgets();
	
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("QuestSystemEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(false)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.2f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(false)
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
				    FTabManager::NewSplitter()
				    ->SetOrientation(Orient_Vertical)
                    ->Split
                    (
                    FTabManager::NewStack()
                        ->SetSizeCoefficient(0.2f)
                        ->SetHideTabWell(false)
                        ->AddTab(PropertiesTabId, ETabState::OpenedTab)
                    )
				    ->Split
                    (
                        FTabManager::NewStack()
                        ->SetSizeCoefficient(0.3f)
                        ->AddTab(SettingsTabId, ETabState::OpenedTab)
                    )
                )
			)
		);

	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;
    
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, QuestSystemEditorAppIdentifier, StandaloneDefaultLayout,
	                                     bCreateDefaultStandaloneMenu,
	                                     bCreateDefaultToolbar, EditingGraph);
    RegenerateMenusAndToolbars();
}

void FAssetEditor_QuestSystemEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_QuestSystemEditor", "Quest System Editor"));
    const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();
    
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
    
	InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_QuestSystemEditor::SpawnTab_Viewport))
		.SetDisplayName( LOCTEXT("ViewportTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
	
	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_QuestSystemEditor::SpawnTab_Details))
		.SetDisplayName( LOCTEXT("PropertiesTab", "Details") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

    InTabManager->RegisterTabSpawner(SettingsTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_QuestSystemEditor::SpawnTab_EditorSettings))
        .SetDisplayName( LOCTEXT("SettingsTab", "Editor Settings") )
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));
}

void FAssetEditor_QuestSystemEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	
	InTabManager->UnregisterTabSpawner(ViewportTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
	InTabManager->UnregisterTabSpawner(SettingsTabId);
}

bool FAssetEditor_QuestSystemEditor::IsAssetEditor() const
{
    if (!FAssetEditorToolkit::IsAssetEditor()) return false;
    return true;
}

void FAssetEditor_QuestSystemEditor::AddReferencedObjects(class FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(EditingGraph);
    Collector.AddReferencedObject(EditingGraph->EdGraph);
}

void FAssetEditor_QuestSystemEditor::CreateInternalWidgets()
{
    UE_LOG(LogAssetEditor_QuestSystemGraph, Warning, TEXT("Internal editor's widgets are creating"));
    
    GraphViewportWidget = CreateGraphEditorWidget();
    
    const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true, this);

    FDetailsViewArgs SettingsViewArgs;
    SettingsViewArgs.bHideSelectionTip = true;
    SettingsViewArgs.NotifyHook = this;

    FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    DetailsView->SetObject(EditingGraph);
    // DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateSP(this, &FAssetEditor_QuestSystemEditorEditor::IsPropertyEditable));
    DetailsView->OnFinishedChangingProperties().AddSP(this, &FAssetEditor_QuestSystemEditor::OnFinishedChangingProperties);
        
    EditorSettingsView = PropertyEditorModule.CreateDetailView(SettingsViewArgs);
    EditorSettingsView->SetObject(GetEditorSettings());
}

UGraphEditorSettings_QuestSystemEditor* FAssetEditor_QuestSystemEditor::GetEditorSettings() const
{
    return EditorSettings;
}

TSharedRef<SDockTab> FAssetEditor_QuestSystemEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);
    UE_LOG(LogAssetEditor_QuestSystemGraph, Warning, TEXT("Details Tab is spawning"));
    
    return SNew(SDockTab)
        //+ SVerticalBox::Slot()
        //.FillHeight(1.0f)
        //.HAlign(HAlign_Fill)
        .TabRole(PanelTab)
		[
		    DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FAssetEditor_QuestSystemEditor::SpawnTab_EditorSettings(const FSpawnTabArgs& Args)
{
    check(Args.GetTabId() == SettingsTabId);
    return SNew(SDockTab)
        .TabRole(PanelTab)
        [
            EditorSettingsView.ToSharedRef()
        ];
}

TSharedRef<SDockTab> FAssetEditor_QuestSystemEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabId);
	return SNew(SDockTab)
		.TabColorScale(GetTabColorScale())
		.TabRole(PanelTab)
		[
			GraphViewportWidget.ToSharedRef()
		];
}

TSharedRef<SGraphEditor> FAssetEditor_QuestSystemEditor::CreateGraphEditorWidget()
{
	check(EditingGraph->EdGraph); // What's this for?
	FGraphAppearanceInfo GraphAppearanceInfo;
	// Allow to use LOCTEXT below
	GraphAppearanceInfo.CornerText = FText::FromString("Quest System Editor");

	CreateCommandList();

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FAssetEditor_QuestSystemEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FAssetEditor_QuestSystemEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FAssetEditor_QuestSystemEditor::OnNodeTitleCommitted);

    // Make title bar
    TSharedRef<SWidget> TitleBarWidget =
        SNew(SBorder)
        .BorderImage(FEditorStyle::GetBrush(TEXT("Graph.TitleBackground")))
        .HAlign(HAlign_Fill)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .HAlign(HAlign_Center)
            .FillWidth(1.f)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("QuestSystemEditorGraphLabel", /* any other */ "Quest Editor"))
                .TextStyle(FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
            ]
        ];
    
	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(EditingGraph->EdGraph->bEditable)
		.Appearance(GraphAppearanceInfo)
        .TitleBar(TitleBarWidget)
		.GraphToEdit(EditingGraph->EdGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(true);
}

void FAssetEditor_QuestSystemEditor::CreateEdGraph()
{
	if (!EditingGraph->EdGraph)
	{
		EditingGraph->EdGraph = CastChecked<UEdGraph_QuestSystemGraph>(FBlueprintEditorUtils::CreateNewGraph(
		    EditingGraph,
		    NAME_None,
		    UEdGraph_QuestSystemGraph::StaticClass(),
		    UAssetQuestSystemGraphSchema::StaticClass()));
		EditingGraph->EdGraph->bAllowDeletion = false;
	}
}

// Need a declaration in .h
// void FAssetEditor_QuestSystemEditor::SetNewEditingObject(UQuestSystemGraph* NewEditingGraph)
// {
//     if (!NewEditingGraph || NewEditingGraph == EditingGraph) return;
//     RemoveEditingObject(EditingGraph);
//     EditingGraph = NewEditingGraph;
//     AddEditingObject(NewEditingGraph);
// }

void FAssetEditor_QuestSystemEditor::RebuildQuestSystemGraph()
{
    // gotta create Log message if Editing graph is nullptr
    if (!EditingGraph) return;
    
    UEdGraph_QuestSystemGraph* EdGraph = Cast<UEdGraph_QuestSystemGraph>(EditingGraph->EdGraph);
    check(EdGraph);

    EdGraph->RebuildGraph();
}

TSharedPtr<SGraphEditor> FAssetEditor_QuestSystemEditor::GetCurrentGraphEditor() const
{
	return GraphViewportWidget;
}

bool FAssetEditor_QuestSystemEditor::IsPropertyEditable() const
{
    return GetCurrentGraphEditor().IsValid() && GetCurrentGraphEditor()->GetCurrentGraph() && GetCurrentGraphEditor()->GetCurrentGraph()->bEditable;
}

void FAssetEditor_QuestSystemEditor::CreateCommandList()
{
	if (GraphEditorCommands.IsValid()) return; // if the list already exists, we don't need to define it

    GraphEditorCommands = MakeShareable(new FUICommandList);
	{
	    GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::SelectAllNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CanSelectAllNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::DeleteSelectedNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CanDeleteNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CopySelectedNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CanCopyNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::PasteNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CanPasteNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CutSelectedNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CanCutNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::DuplicateNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemEditor::CanDuplicateNodes)
			);

	    GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
        FExecuteAction::CreateRaw(this, &FAssetEditor_QuestSystemEditor::OnRenameNode),
        FCanExecuteAction::CreateRaw(this, &FAssetEditor_QuestSystemEditor::CanRenameNodes)
        );
	    
	    GraphEditorCommands->MapAction(FGraphEditorCommands::Get().CreateComment,
        FExecuteAction::CreateRaw(this, &FAssetEditor_QuestSystemEditor::OnCreateComment),
        FCanExecuteAction::CreateRaw(this, &FAssetEditor_QuestSystemEditor::CanCreateComment)
        );
	}
}

void FAssetEditor_QuestSystemEditor::OnGraphChanged(const FEdGraphEditAction& Action)
{

}

FGraphPanelSelectionSet FAssetEditor_QuestSystemEditor::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelectionSet;
	const TSharedPtr<SGraphEditor> FocusedGraphEditor = GetCurrentGraphEditor();

	// todo: Check the content in GraphEditor.h
	if (FocusedGraphEditor.IsValid())
	{
		CurrentSelectionSet = FocusedGraphEditor->GetSelectedNodes();
	}
	return CurrentSelectionSet;
}

bool FAssetEditor_QuestSystemEditor::CanSelectAllNodes() const
{
	return true;
}

void FAssetEditor_QuestSystemEditor::SelectAllNodes()
{
	const TSharedPtr<SGraphEditor> FocusedGraphEditor = GetCurrentGraphEditor();
	if (FocusedGraphEditor.IsValid())
	{
		FocusedGraphEditor->SelectAllNodes();
	}
}

bool FAssetEditor_QuestSystemEditor::CanDeleteNodes() const
{
	// If any of the nodes can be deleted then we should allow deleting
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		const UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanUserDeleteNode())
		{
			return true;
		}
	}
	return false;
}

void FAssetEditor_QuestSystemEditor::DeleteSelectedNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid()) return;

	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	CurrentGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
		if (!EdNode || !EdNode->CanUserDeleteNode()) continue;

		if (UEdGraphNode_QuestSystemGraphNode* QuestSystemEdNode = Cast<UEdGraphNode_QuestSystemGraphNode>(EdNode))
		{
			QuestSystemEdNode->Modify();

			const UEdGraphSchema* Schema = QuestSystemEdNode->GetSchema();
			if (Schema)
			{
				Schema->BreakNodeLinks(*QuestSystemEdNode);
			}
			QuestSystemEdNode->DestroyNode();
		}
		else
		{
			EdNode->Modify();
			EdNode->DestroyNode();
		}
	}
}

bool FAssetEditor_QuestSystemEditor::CanCopyNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanDuplicateNode())
		{
			return true;
		}
	}
	return false;
}

void FAssetEditor_QuestSystemEditor::CopySelectedNodes()
{
	// Export the selected nodes and place the text on the clipboard
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	FString ExportedText;

	for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (!Node)
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		if (UEdNode_QuestSystemGraphEdge* NodeEdge = Cast<UEdNode_QuestSystemGraphEdge>(*SelectedIter))
		{
			const UEdGraphNode_QuestSystemGraphNode* StartNode = NodeEdge->GetStartNode();
			const UEdGraphNode_QuestSystemGraphNode* EndNode = NodeEdge->GetEndNode();

			if (!SelectedNodes.Contains(StartNode) || !SelectedNodes.Contains(EndNode))
			{
				SelectedIter.RemoveCurrent();
				continue;
			}
		}
		Node->PrepareForCopying();
	}
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

void FAssetEditor_QuestSystemEditor::PasteNodes()
{
	if (TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor())
	{
		PasteNodesHere(CurrentGraphEditor->GetPasteLocation());
	}
}

void FAssetEditor_QuestSystemEditor::PasteNodesHere(const FVector2D& Location)
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid()) return;

	if (UEdGraph* EdGraph = CurrentGraphEditor->GetCurrentGraph())
	{
		const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
		EdGraph->Modify();

		CurrentGraphEditor->ClearSelectionSet();

		FString TextToImport;
		FPlatformApplicationMisc::ClipboardPaste(TextToImport);

		TSet<UEdGraphNode*> PastedNodes;

		FVector2D AverageNodePosition(0.0f, 0.0f);

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			const UEdGraphNode* Node = *It;
			AverageNodePosition.X += Node->NodePosX;
			AverageNodePosition.Y += Node->NodePosY;
		}

		if (PastedNodes.Num() > 0)
		{
			const float InvNumNodes = 1.0f / static_cast<float>(PastedNodes.Num());
			AverageNodePosition.X *= InvNumNodes;
			AverageNodePosition.Y *= InvNumNodes;
		}

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			UEdGraphNode* Node = *It;
			CurrentGraphEditor->SetNodeSelection(Node, true);

			Node->NodePosX = (Node->NodePosX - AverageNodePosition.X) + Location.X;
			Node->NodePosY = (Node->NodePosY - AverageNodePosition.Y) + Location.Y;

			Node->SnapToGrid(16);

			// Give new node a different Guid from the old one
			Node->CreateNewGuid();
		}
		// UpdateUI
		CurrentGraphEditor->NotifyGraphChanged();

		if (UObject* GraphOwner = EdGraph->GetOuter())
		{
			GraphOwner->PostEditChange();
			GraphOwner->MarkPackageDirty();
		}
	}
}

bool FAssetEditor_QuestSystemEditor::CanPasteNodes() const
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid()) return false;

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(CurrentGraphEditor->GetCurrentGraph(), ClipboardContent);
}

void FAssetEditor_QuestSystemEditor::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

bool FAssetEditor_QuestSystemEditor::CanCutNodes() const
{
	return CanCopyNodes() && CanDeleteNodes();
}

bool FAssetEditor_QuestSystemEditor::CanDuplicateNodes() const
{
	return CanCopyNodes();;
}

void FAssetEditor_QuestSystemEditor::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

bool FAssetEditor_QuestSystemEditor::CanRenameNodes() const
{
    /**
     * Renaming is allowed to any node for now, 
     * but better way to implement this function is by using GraphEditorSettings pointer.
     * GraphEditorSettings contains options and permissions for graph nodes.
     * We should also be able to rename only one node at a same time.
     */
    return GetSelectedNodes().Num() == 1;
}

void FAssetEditor_QuestSystemEditor::OnRenameNode()
{
    TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
    if (!CurrentGraphEditor.IsValid()) return;

    const FGraphPanelSelectionSet SelectedNode = CurrentGraphEditor->GetSelectedNodes();

    UEdGraphNode* Node = Cast<UEdGraphNode>(*(FGraphPanelSelectionSet::TConstIterator(SelectedNode)));

    if (Node && Node->bCanRenameNode)
    {
        CurrentGraphEditor->IsNodeTitleVisible(Node, true);
    }
}

void FAssetEditor_QuestSystemEditor::DeleteSelectedDuplicatableNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid()) return;

	const FGraphPanelSelectionSet OldSelectedNodes = CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanDuplicateNode())
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}
	// Delete the duplicatable nodes
	DeleteSelectedNodes();
	
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter))
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}
}

// TODO: add possibility to create comments (not neccessary I think cause )
void FAssetEditor_QuestSystemEditor::OnCreateComment() {}

bool FAssetEditor_QuestSystemEditor::CanCreateComment() { return true; }

// TODO: make nodes showing up in the property view on selecting
void FAssetEditor_QuestSystemEditor::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
    TArray<UObject*> Selection;

    for (const auto& SelectionEntry : NewSelection)
    {
        Selection.Add(SelectionEntry);
    }

    if (Selection.Num() == 1)
    {
        DetailsView->SetObjects(Selection);
        DetailsView->ShowAllAdvancedProperties();
    }
    else
    {
        DetailsView->SetObject(EditingGraph);
    }
}

void FAssetEditor_QuestSystemEditor::OnNodeDoubleClicked(UEdGraphNode* Node)
{
    if (GraphEditorCommands->TryExecuteAction((FGenericCommands::Get().Rename).ToSharedRef()))
    {
        UE_LOG(LogAssetEditor_QuestSystemGraph, Warning, TEXT("OnNodeDoubleClicked is called"));
    }
}

void FAssetEditor_QuestSystemEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
    if (!EditingGraph) return;
    EditingGraph->EdGraph->GetSchema()->ForceVisualizationCacheClear();

    RebuildQuestSystemGraph();
}

void FAssetEditor_QuestSystemEditor::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{

}

void FAssetEditor_QuestSystemEditor::ShowMessage()
{
}

FName FAssetEditor_QuestSystemEditor::GetToolkitFName() const
{
	return FName("FQuestSystemGraphEditor");
}

FText FAssetEditor_QuestSystemEditor::GetBaseToolkitName() const
{
	return FText::FromString("QuestSystemGraph EditorToolkitName");
}

FString FAssetEditor_QuestSystemEditor::GetWorldCentricTabPrefix() const
{
	return FString("QuestSystemGraph Editor");
}

FLinearColor FAssetEditor_QuestSystemEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

#undef LOCTEXT_NAMESPACE