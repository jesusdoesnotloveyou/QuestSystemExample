// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphEdge.h"

void SGraphNode_QuestSystemGraphEdge::Construct(const FArguments& InArgs, UEdNode_QuestSystemGraphEdge* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}
