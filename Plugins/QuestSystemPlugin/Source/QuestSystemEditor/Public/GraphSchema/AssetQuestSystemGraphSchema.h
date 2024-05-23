// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Ed/EdGraphNode_QuestSystemGraphNode.h"
#include "Ed/EdNode_QuestSystemGraphEdge.h"
#include "EdGraph/EdGraphSchema.h"
#include "AssetQuestSystemGraphSchema.generated.h"

class UEdGraphPin;
class UEdGraphNode_QuestSystemGraphNode;
class UEdNode_QuestSystemGraphEdge;

/** Action to add a node to the graph */
USTRUCT()
struct QUESTSYSTEMEDITOR_API FEdGraphSchemaAction_QuestSystemEditor_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()
    
    /** Template of node we want to create */
    UPROPERTY()
	class UEdGraphNode_QuestSystemGraphNode* NodeTemplate;

	FEdGraphSchemaAction_QuestSystemEditor_NewNode()
    : FEdGraphSchemaAction()
    , NodeTemplate(nullptr) {}
    
	FEdGraphSchemaAction_QuestSystemEditor_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
	: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
    , NodeTemplate(nullptr) {}

    // FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
    virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
    // End of FEdGraphSchemaAction interface

    // template <typename NodeType>
    // static NodeType* SpawnNodeFromTemplate(class UEdGraph* ParentGraph, NodeType* InTemplateNode, const FVector2D Location)
    // {
    //     FEdGraphSchemaAction_QuestSystemEditor_NewNode Action;
    //     Action.NodeTemplate = InTemplateNode;
    //     return Cast<NodeType>(Action.PerformAction(ParentGraph, nullptr, Location));
    // }
};

USTRUCT()
struct QUESTSYSTEMEDITOR_API FEdGraphSchemaAction_QuestSystemEditor_NewEdge : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()
    
    /** Template of node we want to create */
    UPROPERTY()
	UEdNode_QuestSystemGraphEdge* NodeTemplate;

	FEdGraphSchemaAction_QuestSystemEditor_NewEdge()
    : FEdGraphSchemaAction()
    , NodeTemplate(nullptr) {}
    
	FEdGraphSchemaAction_QuestSystemEditor_NewEdge(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
	: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
    , NodeTemplate(nullptr) {}

    // FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
    //virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
    // End of FEdGraphSchemaAction interface

    // template <typename NodeType>
    // static NodeType* SpawnNodeFromTemplate(class UEdGraph* ParentGraph, NodeType* InTemplateNode, const FVector2D Location)
    // {
    //     FEdGraphSchemaAction_QuestSystemEditor_NewNode Action;
    //     Action.NodeTemplate = InTemplateNode;
    //     return Cast<NodeType>(Action.PerformAction(ParentGraph, nullptr, Location));
    // }
};

UCLASS()
class QUESTSYSTEMEDITOR_API UAssetQuestSystemGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
public:
	//~ Begin EdGraphSchema Interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
    void GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin* InGraphPin);
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
    virtual EGraphType GetGraphType(const UEdGraph *TestEdGraph) const override;
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual const FPinConnectionResponse CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const override;
	virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;
    virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin *A, UEdGraphPin *B) const override;
    
    //virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect &InClippingRect, FSlateWindowElementList &InDrawElements, UEdGraph *InGraphObj) const override;

    virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
    virtual void BreakNodeLinks(UEdGraphNode &TargetNode) const override;
    virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;
    virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

    //virtual UEdGraphPin* DropPinOnNode(UEdGraphNode *InTargetNode, const FName &InSourcePinName, const FEdGraphPinType &InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;
    //virtual bool SupportsDropPinOnNode(UEdGraphNode *InTargetNode, const FEdGraphPinType &InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText &OutErrorMessage) const override;

	virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;
	virtual int32 GetCurrentVisualizationCacheID() const override;
	virtual void ForceVisualizationCacheClear() const override;
    
    // virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;
	// virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;
    
    // ~ End EdGraphSchema Interface

protected:
    // for next changes of schema and nodes
    // for now that function does nothing
    static TSharedPtr<FEdGraphSchemaAction_QuestSystemEditor_NewNode> AddNewNodeAction(FGraphActionListBuilderBase& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip);

private:
    // ID for checking dirty status of node titles against, increases whenever 
    static int32 CurrentCacheRefreshID;
};
