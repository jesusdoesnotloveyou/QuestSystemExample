// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/K2Node_QuestSystemNode.h"

// SGraphNode_QuestSystemGraphNode
void SGraphNode_QuestSystemGraphNode::Construct(const FArguments& InArgs, UEdGraphNode_QuestSystemGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

// SGraphNode_QuestSystemK2GraphNode
void SGraphNode_QuestSystemK2GraphNode::Construct(const FArguments& InArgs, UK2Node_QuestSystemNode* InNode)
{
    GraphNode = InNode;
    UpdateGraphNode();
}
