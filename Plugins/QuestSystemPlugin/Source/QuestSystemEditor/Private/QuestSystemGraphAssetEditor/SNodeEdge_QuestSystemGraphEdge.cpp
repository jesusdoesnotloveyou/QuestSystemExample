// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/SNodeEdge_QuestSystemGraphEdge.h"

void SNodeEdge_QuestSystemGraphEdge::Construct(const FArguments& InArgs, UEdNodeEdge_QuestSystemGraphEdge* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}
