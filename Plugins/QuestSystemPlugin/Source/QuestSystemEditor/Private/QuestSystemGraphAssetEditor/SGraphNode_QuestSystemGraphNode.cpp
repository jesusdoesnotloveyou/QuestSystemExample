// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"

// SGraphNode_QuestSystemGraphNode
void SGraphNode_QuestSystemGraphNode::Construct(const FArguments& InArgs, UEdGraphNode_QuestSystemGraphNode* InNode)
{
	GraphNode = InNode;

    SetCursor(EMouseCursor::CardinalCross);
    
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

void SGraphNode_QuestSystemGraphNode::AddPin(const TSharedRef<SGraphPin> &PinToAdd)
{
    SGraphNode::AddPin(PinToAdd);
}

bool SGraphNode_QuestSystemGraphNode::IsNameReadOnly() const
{
    return SGraphNode::IsNameReadOnly();
}
