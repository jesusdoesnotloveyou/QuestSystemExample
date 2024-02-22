// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"

// SGraphNode_QuestSystemGraphNode
void SGraphNode_QuestSystemGraphNode::Construct(const FArguments& InArgs, UEdGraphNode_QuestSystemGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
    InNode->SEdNode = this;
}

void SGraphNode_QuestSystemGraphNode::UpdateGraphNode()
{
    SGraphNode::UpdateGraphNode();
}

void SGraphNode_QuestSystemGraphNode::CreatePinWidgets()
{
    SGraphNode::CreatePinWidgets();
}

// // SGraphNode_QuestSystemK2GraphNode
// void SGraphNode_QuestSystemK2GraphNode::Construct(const FArguments& InArgs, UK2Node_QuestSystemNode* InNode)
// {
//     GraphNode = InNode;
//     UpdateGraphNode();
// }
