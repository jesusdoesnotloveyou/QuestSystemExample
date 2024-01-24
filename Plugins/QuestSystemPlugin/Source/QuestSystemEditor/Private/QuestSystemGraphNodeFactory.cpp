// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphNodeFactory.h"
#include "EdGraph/EdGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdNodeEdge_QuestSystemGraphEdge.h"
#include "QuestSystemGraphAssetEditor/SNodeEdge_QuestSystemGraphEdge.h"

#include "QuestSystemGraphAssetEditor/K2Node_QuestSystemNode.h"

TSharedPtr<SGraphNode> FQuestSystemGraphNodeFactory::CreateNode(UEdGraphNode* Node) const
{
    if (UEdGraphNode* BaseGraphNode = Cast<UEdGraphNode>(Node))
    {
        if (UEdGraphNode_QuestSystemGraphNode* EdGraphNode = Cast<UEdGraphNode_QuestSystemGraphNode>(Node))
        {
            return SNew(SGraphNode_QuestSystemGraphNode, EdGraphNode);
        }
        // if (UEdNodeEdge_QuestSystemGraphEdge* EdNodeEdge = Cast<UEdNodeEdge_QuestSystemGraphEdge>(Node))
        // {
        // 	return SNew(SNodeEdge_QuestSystemGraphEdge, EdNodeEdge);
        // }
        if (UK2Node_QuestSystemNode* EdGraphK2Node = Cast<UK2Node_QuestSystemNode>(Node))
        {
            return SNew(SGraphNode_QuestSystemK2GraphNode, EdGraphK2Node);
        }
    }
    return nullptr;
}

// TSharedPtr<class SGraphPin> FQuestSystemGraphNodePinFactory::CreatePin(class UEdGraphPin* Pin) const
// {
// 	return nullptr;
// }
