// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/AssetEditor_QuestSystemGraph.h"

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
#include "QuestSystemGraphAssetEditor/EdGraphSchema_K2_QuestSystem.h"
#include "QuestSystemGraphAssetEditor/EdNodeEdge_QuestSystemGraphEdge.h"

DEFINE_LOG_CATEGORY_STATIC(AssetEditr_QuestSystemGraph, All, All);

#define LOCTEXT_NAMESPACE "QuestSystemEditor"

const FName FAssetEditor_QuestSystemGraph::QuestSystemEditorAppIdentifier( TEXT("QuestSystemEditorApp") );

const FName FAssetEditor_QuestSystemGraph::PropertiesTabId( TEXT ("QuestSystemEditor_Properties" ) );
const FName FAssetEditor_QuestSystemGraph::ViewportTabId( TEXT ("QuestSystemEditor_Viewport" ) );
const FName FAssetEditor_QuestSystemGraph::SettingsTabId( TEXT ("QuestSystemEditor_Settings" ) );

FAssetEditor_QuestSystemGraph::FAssetEditor_QuestSystemGraph()
{
	EditorGraph = nullptr;
    EditorSettings = nullptr;
}

FAssetEditor_QuestSystemGraph::~FAssetEditor_QuestSystemGraph()
{
	
}

/** TODO : Try to implement test action for Toolbar buttons */
void FAssetEditor_QuestSystemGraph::CreateNewNode()
{
    if (!EditorGraph || !EditorGraph->EdGraph) return;
    //EditorGraph->EdGraph->;
}

bool FAssetEditor_QuestSystemGraph::CanCreateNewNode() const
{
    return true;
}

void FAssetEditor_QuestSystemGraph::InitQuestSystemAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UQuestSystemGraph* GraphToEdit)
{
	EditorGraph = GraphToEdit;
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

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
    
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, QuestSystemEditorAppIdentifier, StandaloneDefaultLayout,
	                                     bCreateDefaultStandaloneMenu,
	                                     bCreateDefaultToolbar, EditorGraph);
}

void FAssetEditor_QuestSystemGraph::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_QuestSystemEditor", "Quest System Editor"));
	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
    
	InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_QuestSystemGraph::SpawnTab_Viewport))
		.SetDisplayName( LOCTEXT("ViewportTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
	
	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_QuestSystemGraph::SpawnTab_Details))
		.SetDisplayName( LOCTEXT("PropertiesTab", "Details") )
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

    InTabManager->RegisterTabSpawner(SettingsTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_QuestSystemGraph::SpawnTab_EditorSettings))
        .SetDisplayName( LOCTEXT("SettingsTab", "Editor Settings") )
        .SetGroup(WorkspaceMenuCategory.ToSharedRef())
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FAssetEditor_QuestSystemGraph::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	
	InTabManager->UnregisterTabSpawner(ViewportTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
	InTabManager->UnregisterTabSpawner(SettingsTabId);
}

void FAssetEditor_QuestSystemGraph::AddReferencedObjects(class FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(EditorGraph);
    Collector.AddReferencedObject(EditorGraph->EdGraph);
}

void FAssetEditor_QuestSystemGraph::CreateInternalWidgets()
{
    UE_LOG(AssetEditr_QuestSystemGraph, Warning, TEXT("Internal editor's widgets are creating"));

    GraphViewportWidget = CreateGraphEditorWidget();
    
    const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true, this);

    FDetailsViewArgs SettingsViewArgs;
    SettingsViewArgs.bHideSelectionTip = true;
    SettingsViewArgs.NotifyHook = this;

    FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    DetailsView->SetObject(EditorGraph);
    // DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateSP(this, &FAssetEditor_QuestSystemGraph::IsPropertyEditable));
    // DetailsView->OnFinishedChangingProperties().AddSP(this, &FAssetEditor_QuestSystemGraph::OnFinishedChangingProperties);
        
    EditorSettingsView = PropertyEditorModule.CreateDetailView(SettingsViewArgs);
    EditorSettingsView->SetObject(GetEditorSettings());
    
    //GEditor->GetEditorWorldContext().World(); // Getting World in plugins
}

UGraphEditorSettings_QuestSystemEditor* FAssetEditor_QuestSystemGraph::GetEditorSettings() const
{
    return EditorSettings;
}

TSharedRef<SDockTab> FAssetEditor_QuestSystemGraph::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);
    UE_LOG(AssetEditr_QuestSystemGraph, Warning, TEXT("Details Tab is spawning"));
    
    return SNew(SDockTab)
        //+ SVerticalBox::Slot()
        //.FillHeight(1.0f)
        //.HAlign(HAlign_Fill)
        .TabRole(ETabRole::PanelTab)
		[
		    DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FAssetEditor_QuestSystemGraph::SpawnTab_EditorSettings(const FSpawnTabArgs& Args)
{
    check(Args.GetTabId() == SettingsTabId);
    return SNew(SDockTab)
        .TabRole(PanelTab)
        [
            EditorSettingsView.ToSharedRef()
        ];
}

TSharedRef<SDockTab> FAssetEditor_QuestSystemGraph::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabId);
	return SNew(SDockTab)
		.TabColorScale(GetTabColorScale())
		.TabRole(PanelTab)
		[
			GraphViewportWidget.ToSharedRef()
		];
}

TSharedRef<SGraphEditor> FAssetEditor_QuestSystemGraph::CreateGraphEditorWidget()
{
	check(EditorGraph->EdGraph); // What's this for?
	FGraphAppearanceInfo GraphAppearanceInfo;
	// Allow to use LOCTEXT below
	GraphAppearanceInfo.CornerText = FText::FromString("Quest System Editor");

	CreateCommandList();

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FAssetEditor_QuestSystemGraph::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FAssetEditor_QuestSystemGraph::OnNodeDoubleClicked);
    InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FAssetEditor_QuestSystemGraph::OnNodeTitleCommitted);

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
		.IsEditable(EditorGraph->EdGraph->bEditable)
		.Appearance(GraphAppearanceInfo)
        .TitleBar(TitleBarWidget)
		.GraphToEdit(EditorGraph->EdGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(true);
}

void FAssetEditor_QuestSystemGraph::CreateEdGraph()
{
	if (!EditorGraph->EdGraph)
	{
		EditorGraph->EdGraph = CastChecked<UEdGraph_QuestSystemGraph>(FBlueprintEditorUtils::CreateNewGraph(
		    EditorGraph,
		    NAME_None,
		    UEdGraph_QuestSystemGraph::StaticClass(),
		    //UAssetQuestSystemGraphSchema::StaticClass()));
		    UEdGraphSchema_K2_QuestSystem::StaticClass()));
		EditorGraph->EdGraph->bAllowDeletion = false;
	}
}

TSharedPtr<SGraphEditor> FAssetEditor_QuestSystemGraph::GetCurrentGraphEditor() const
{
	return GraphViewportWidget;
}

bool FAssetEditor_QuestSystemGraph::IsPropertyEditable() const
{
    return GetCurrentGraphEditor().IsValid() && GetCurrentGraphEditor()->GetCurrentGraph() && GetCurrentGraphEditor()->GetCurrentGraph()->bEditable;
}

void FAssetEditor_QuestSystemGraph::CreateCommandList()
{
	if (GraphEditorCommands.IsValid()) return; // if the list already exists, we don't need to define it
	GraphEditorCommands = MakeShareable(new FUICommandList);
	{
	    GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::SelectAllNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CanSelectAllNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::DeleteSelectedNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CanDeleteNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CopySelectedNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CanCopyNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::PasteNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CanPasteNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CutSelectedNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CanCutNodes)
			);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::DuplicateNodes),
			FCanExecuteAction::CreateSP(this, &FAssetEditor_QuestSystemGraph::CanDuplicateNodes)
			);
	    GraphEditorCommands->MapAction(FGraphEditorCommands::Get().CreateComment,
        FExecuteAction::CreateRaw(this, &FAssetEditor_QuestSystemGraph::OnCreateComment),
        FCanExecuteAction::CreateRaw(this, &FAssetEditor_QuestSystemGraph::CanCreateComment)
    );
	}
}

void FAssetEditor_QuestSystemGraph::OnGraphChanged(const FEdGraphEditAction& Action)
{
}

FGraphPanelSelectionSet FAssetEditor_QuestSystemGraph::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelectionSet;
	const TSharedPtr<SGraphEditor> FocusedGraphEditor = GetCurrentGraphEditor();

	// TO DO: check the difference between IsValid and if()
	// Check the content in GraphEditor.h
	if (FocusedGraphEditor.IsValid())
	{
		CurrentSelectionSet = FocusedGraphEditor->GetSelectedNodes();
	}
	return CurrentSelectionSet;
}

bool FAssetEditor_QuestSystemGraph::CanSelectAllNodes() const
{
	return true;
}

void FAssetEditor_QuestSystemGraph::SelectAllNodes()
{
	const TSharedPtr<SGraphEditor> FocusedGraphEditor = GetCurrentGraphEditor();
	if (FocusedGraphEditor.IsValid())
	{
		FocusedGraphEditor->SelectAllNodes();
	}
}

bool FAssetEditor_QuestSystemGraph::CanDeleteNodes() const
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

void FAssetEditor_QuestSystemGraph::DeleteSelectedNodes()
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

bool FAssetEditor_QuestSystemGraph::CanCopyNodes() const
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

void FAssetEditor_QuestSystemGraph::CopySelectedNodes()
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

		if (UEdNodeEdge_QuestSystemGraphEdge* NodeEdge = Cast<UEdNodeEdge_QuestSystemGraphEdge>(*SelectedIter))
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

void FAssetEditor_QuestSystemGraph::PasteNodes()
{
	if (TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor())
	{
		PasteNodesHere(CurrentGraphEditor->GetPasteLocation());
	}
}

void FAssetEditor_QuestSystemGraph::PasteNodesHere(const FVector2D& Location)
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

bool FAssetEditor_QuestSystemGraph::CanPasteNodes() const
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid()) return false;

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(CurrentGraphEditor->GetCurrentGraph(), ClipboardContent);
}

void FAssetEditor_QuestSystemGraph::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

bool FAssetEditor_QuestSystemGraph::CanCutNodes() const
{
	return CanCopyNodes() && CanDeleteNodes();
}

bool FAssetEditor_QuestSystemGraph::CanDuplicateNodes() const
{
	return CanCopyNodes();;
}

void FAssetEditor_QuestSystemGraph::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

void FAssetEditor_QuestSystemGraph::DeleteSelectedDuplicatableNodes()
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

void FAssetEditor_QuestSystemGraph::OnCreateComment()
{
    
}

bool FAssetEditor_QuestSystemGraph::CanCreateComment()
{
    return true;
}

// TODO: make nodes showing up in the property view on selecting
void FAssetEditor_QuestSystemGraph::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
}

void FAssetEditor_QuestSystemGraph::OnNodeDoubleClicked(UEdGraphNode* Node)
{
}

void FAssetEditor_QuestSystemGraph::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{
}

void FAssetEditor_QuestSystemGraph::ShowMessage()
{
}

FName FAssetEditor_QuestSystemGraph::GetToolkitFName() const
{
	return FName("FQuestSystemGraphEditor");
}

FText FAssetEditor_QuestSystemGraph::GetBaseToolkitName() const
{
	return FText::FromString("QuestSystemGraph EditorToolkitName");
}

FString FAssetEditor_QuestSystemGraph::GetWorldCentricTabPrefix() const
{
	return FString("QuestSystemGraph Editor");
}

FLinearColor FAssetEditor_QuestSystemGraph::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

#undef LOCTEXT_NAMESPACE