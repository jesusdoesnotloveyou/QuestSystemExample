// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphNodeFactory.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphSchema//AssetQuestSystemGraphSchema.h"
#include "Ed/EdGraphNode_QuestSystemGraphNode.h"
#include "Ed/EdNode_QuestSystemGraphEdge.h"
#include "Ed/SGraphNode_QuestSystemGraphNode.h"
#include "Ed/SGraphNode_QuestSystemGraphEdge.h"
#include "QuestSystemGraphAssetEditor/ConnectionDrawingPolicy_QuestSystemEditor.h"
#include "KismetPins/SGraphPinExec.h"

TSharedPtr<SGraphNode> FQuestSystemGraphNodeFactory::CreateNode(UEdGraphNode *Node) const
{
    if (UEdGraphNode_QuestSystemGraphNode* EdNode_GraphNode = Cast<UEdGraphNode_QuestSystemGraphNode>(Node))
    {
        return SNew(SGraphNode_QuestSystemGraphNode, EdNode_GraphNode);
    }
    if (UEdNode_QuestSystemGraphEdge* EdNode_Edge = Cast<UEdNode_QuestSystemGraphEdge>(Node))
    {
        return SNew(SGraphNode_QuestSystemGraphEdge, EdNode_Edge);
    }
    return nullptr;
}

TSharedPtr<class SGraphPin> FQuestSystemGraphNodePinFactory::CreatePin(class UEdGraphPin* Pin) const 
{
    if (Pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec)
    {
    	return SNew(SGraphPinExec, Pin);
    }
    return nullptr;
}

class FConnectionDrawingPolicy* FQuestSystemGraphPinConnectionFactory::CreateConnectionPolicy(const class UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const class FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
    if (Schema->IsA(UAssetQuestSystemGraphSchema::StaticClass()))
    {
        return new FConnectionDrawingPolicy_QuestSystemEditor(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);
    }
    return nullptr;
}