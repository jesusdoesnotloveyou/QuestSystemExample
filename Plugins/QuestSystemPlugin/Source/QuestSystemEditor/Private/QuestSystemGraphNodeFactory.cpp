// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphNodeFactory.h"
#include "EdGraph/EdGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdNode_QuestSystemGraphEdge.h"
#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphEdge.h"

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
