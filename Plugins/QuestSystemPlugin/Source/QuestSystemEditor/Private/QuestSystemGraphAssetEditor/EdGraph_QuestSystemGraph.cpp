// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/EdGraph_QuestSystemGraph.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraph.h"
#include "Animation/NodeMappingContainer.h"

UEdGraph_QuestSystemGraph::UEdGraph_QuestSystemGraph()
{
	
}

UEdGraph_QuestSystemGraph::~UEdGraph_QuestSystemGraph()
{
	
}

UQuestSystemGraph* UEdGraph_QuestSystemGraph::GetGenericGraph() const
{
	return CastChecked<UQuestSystemGraph>(GetOuter());
}

void UEdGraph_QuestSystemGraph::RebuildGraph()
{
	
}

bool UEdGraph_QuestSystemGraph::Modify(bool bAlwaysMarkDirty)
{
	const bool bNeedToModify = Super::Modify(bAlwaysMarkDirty);
	GetGenericGraph()->Modify();
	for (const auto& Node : Nodes)
	{
		Node->Modify();
	}
	
	return bNeedToModify;
}

void UEdGraph_QuestSystemGraph::Clear()
{
	GetGenericGraph()->ClearGraph();
	NodeMap.Reset();
	// EdgeMap.Reset();

	for (const auto& Node : Nodes)
	{
		if (UEdGraphNode_QuestSystemGraphNode* UEdNode = Cast<UEdGraphNode_QuestSystemGraphNode>(Node))
		{
			UQuestSystemGraphNode* QuestSystemGraphNode = UEdNode->QuestSystemGraphNode;
			if (QuestSystemGraphNode)
			{
				QuestSystemGraphNode->ParentNodes.Reset();
				QuestSystemGraphNode->ChildrenNodes.Reset();
				QuestSystemGraphNode->Edges.Reset();
			}
		}
	}
}

void UEdGraph_QuestSystemGraph::SortNodes(UQuestSystemGraphNode* RootNode)
{
	
}

void UEdGraph_QuestSystemGraph::PostEditUndo()
{
    Super::PostEditUndo();
    NotifyGraphChanged();
}