// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Tools/BaseAssetToolkit.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "GraphEditor.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FAssetQuestEditorToolbar;
class UQuestSystemGraph;
class UGraphEditorSettings_QuestSystemEditor;

// For FWorkflowCentricApplication inherited editor (example of this type editor - behavior tree) 
struct FTestDetailsSummoner : public FWorkflowTabFactory
{
    FTestDetailsSummoner();
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
                               UQuestSystemGraph *GraphToEdit);

    virtual void RegisterTabSpawners(const TSharedRef<FTabManager> &InTabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager> &InTabManager) override;

    // Inherited from FGCObject
    virtual void AddReferencedObjects(class FReferenceCollector &Collector) override;

    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    // virtual FText GetToolkitName() const override;
    // virtual FText GetToolkitToolTipText() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    //virtual FString GetDocumentationLink() const override;
    //virtual void SaveAsset_Execute() override;

    UGraphEditorSettings_QuestSystemEditor *GetEditorSettings() const;

protected:
    TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs &Args);
    TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs &Args);
    TSharedRef<SDockTab> SpawnTab_EditorSettings(const FSpawnTabArgs &Args);

private:
    TSharedRef<SGraphEditor> CreateGraphEditorWidget();
    void CreateInternalWidgets();

    void RebuildQuestSystemGraph();
    
    void CreateEdGraph();

    bool IsPropertyEditable() const;

private:
    /**	The tab ids for all the tabs used */
    static const FName ViewportTabId;

    /**	The tab ids for all the tabs used */
    static const FName PropertiesTabId;

    /**	The tab ids for all the tabs used */
    static const FName SettingsTabId;

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

    void OnCreateComment();
    bool CanCreateComment();

    /** Called when the selection changes in the GraphEditor */
    void OnSelectedNodesChanged(const TSet<UObject*> &NewSelection);

    /** Called when a node is double clicked */
    void OnNodeDoubleClicked(UEdGraphNode* Node);
    
    void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);
    
    /** Called when a node's title is committed for a rename */
    void OnNodeTitleCommitted(const FText &NewText, ETextCommit::Type CommitInfo, UEdGraphNode *NodeBeingChanged);

    void ShowMessage();

protected:
    UGraphEditorSettings_QuestSystemEditor *EditorSettings;

    UQuestSystemGraph *EditingGraph;

    //Toolbar
    TSharedPtr<class FAssetQuestEditorToolbar> ToolbarBuilder;

    TSharedPtr<SGraphEditor> GraphViewportWidget;
    TSharedPtr<IDetailsView> DetailsView;
    TSharedPtr<IDetailsView> EditorSettingsView;

    /** The command list for this editor */
    TSharedPtr<class FUICommandList> GraphEditorCommands;
    
    TSharedPtr<SGraphEditor> GetCurrentGraphEditor() const;
    void CreateCommandList();
};
