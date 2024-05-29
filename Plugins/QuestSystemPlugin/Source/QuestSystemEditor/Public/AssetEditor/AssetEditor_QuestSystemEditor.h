// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Tools/BaseAssetToolkit.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "GraphEditor.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

// Forward declarations
class FAssetQuestEditorToolbar;
class UQuestSystemGraph;
class UGraphEditorSettings_QuestSystemEditor;

struct FQuestSystemEditorTabs
{
    /**	The tab ids for all the tabs used */
    static const FName ViewportTabId;

    /**	The tab ids for all the tabs used */
    static const FName PropertiesTabId;

    /**	The tab ids for all the tabs used */
    static const FName SettingsTabId;

    /** The tab ids for level preview */
    static const FName PreviewTabId;
};

// For FWorkflowCentricApplication inherited editor (example of this type editor - behavior tree) 
struct FQuestSystemGraphDetailsSummoner : public FWorkflowTabFactory
{
public:
    FQuestSystemGraphDetailsSummoner(TSharedPtr<class FAssetEditor_QuestSystemEditor> InQuestEditorPtr);
    virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
    virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
    TWeakPtr<class FAssetEditor_QuestSystemEditor> QuestEditorPtr;
};

class QUESTSYSTEMEDITOR_API FAssetEditor_QuestSystemEditor
    : public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public:
    FAssetEditor_QuestSystemEditor();
    virtual ~FAssetEditor_QuestSystemEditor() override;

    //~ Test functions for node creating
    void CreateNewNode();
    bool CanCreateNewNode() const;
    //~

    void InitQuestSystemEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost> &InitToolkitHost,
                               UObject *ObjectToEdit);
    
    //~ Begin of FGCObject Interface
    virtual void AddReferencedObjects(class FReferenceCollector &Collector) override;
    //~ End of FGCObject Interface

    //~ Begin of IToolkit Interface
    virtual void RegisterTabSpawners(const TSharedRef<FTabManager> &InTabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager> &InTabManager) override;
    virtual bool IsAssetEditor() const override;
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    // virtual FText GetToolkitName() const override;
    // virtual FText GetToolkitToolTipText() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;
    //~ End of IToolkit Interface

    // Inherited form FAssetEditorToolkit
    //virtual FString GetDocumentationLink() const override;
    //virtual void SaveAsset_Execute() override;

    UGraphEditorSettings_QuestSystemEditor* GetEditorSettings() const;

protected:
    TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs &Args);
    TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs &Args);
    TSharedRef<SDockTab> SpawnTab_Preview(const FSpawnTabArgs &Args);
    TSharedRef<SDockTab> SpawnTab_EditorSettings(const FSpawnTabArgs &Args);

    void ExtendMenu();
    void ExtendToolbar();
    
private:
    TSharedRef<SGraphEditor> CreateGraphEditorWidget();
    TSharedRef<SDockTab> CreatePreviewWidget();
    void CreateInternalWidgets();

    void CreateEdGraph();
    void RebuildQuestSystemGraph();

    bool IsPropertyEditable() const;

public:
    /** App Identifier. Technically, all simple editors are the same app, despite editing a variety of assets. */
    static const FName QuestSystemEditorAppIdentifier;

protected:
    void OnGraphChanged(const FEdGraphEditAction &Action);

    FGraphPanelSelectionSet GetSelectedNodes() const;

    bool CanSelectAllNodes() const;
    void SelectAllNodes();

    bool CanDeleteNodes() const;
    void DeleteSelectedNodes();

    bool CanCopyNodes() const;
    void CopySelectedNodes();

    bool CanPasteNodes() const;
    void PasteNodes();
    void PasteNodesHere(const FVector2D &Location);

    bool CanCutNodes() const;
    void CutSelectedNodes();

    bool CanDuplicateNodes() const;
    void DuplicateNodes();
    void DeleteSelectedDuplicatableNodes();

    bool CanRenameNodes() const;
    void OnRenameNode();

    void OnCreateComment();
    bool CanCreateComment();

    // Delegates
    /** Called when the selection changes in the GraphEditor */
    void OnSelectedNodesChanged(const TSet<UObject*> &NewSelection);
    /** Called when a node is double clicked */
    void OnNodeDoubleClicked(UEdGraphNode* Node);
    /** Called when a node's title is committed for a rename */
    void OnNodeTitleCommitted(const FText &NewText, ETextCommit::Type CommitInfo, UEdGraphNode *NodeBeingChanged);
    void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);
    
    void ShowMessage();

protected:
    UGraphEditorSettings_QuestSystemEditor* EditorSettings;

    // The object we're currently editing
    UQuestSystemGraph* EditingGraph;
    
    //Toolbar
    TSharedPtr<class FAssetQuestEditorToolbar> ToolbarBuilder;

    TSharedPtr<SGraphEditor> GraphViewportWidget;
    // Gotta change to custom editor viewport SWidget 
    TSharedPtr<SWidget> PreviewWidget;
    TSharedPtr<IDetailsView> DetailsView;
    TSharedPtr<IDetailsView> EditorSettingsView;

    /** The command list for this editor */
    TSharedPtr<class FUICommandList> GraphEditorCommands;
    
    TSharedPtr<SGraphEditor> GetCurrentGraphEditor() const;
    void CreateCommandList();
};
