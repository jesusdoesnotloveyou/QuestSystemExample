// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraph.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestSystemGraph, All, All);

#define LOCTEXT_NAMESPACE "QuestSystemGraph"

UQuestSystemGraph::UQuestSystemGraph()
{
	NodeType = UQuestSystemGraphNode::StaticClass();
	EdgeType = UQuestSystemGraphEdge::StaticClass();

	bEdgeEnabled = true;
	
#if WITH_EDITORONLY_DATA
	EdGraph = nullptr;
	
	bCanRenameNode = true;
	
#endif
}

UQuestSystemGraph::~UQuestSystemGraph()
{
	
}

void UQuestSystemGraph::Print(bool ToConsole, bool ToScreen)
{
	int Level = 0;
	TArray<UQuestSystemGraphNode*> CurrentLevelNodes = RootNodes;
	TArray<UQuestSystemGraphNode*> NextLevelNodes;

	while(CurrentLevelNodes.Num() != 0)
	{
		for (int32 i = 0; i < CurrentLevelNodes.Num(); ++i)
		{
			UQuestSystemGraphNode* Node = CurrentLevelNodes[i];
			check(Node);

			FString Message = FString::Printf(TEXT("%s, Level %d"), *Node->GetDescription().ToString(), Level);

			if (ToConsole)
			{
				UE_LOG(LogQuestSystemGraph, Display, TEXT("%s"), *Message);
			}
			if (ToScreen && GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, Message);
			}
			for (int32 j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}
		CurrentLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}

int UQuestSystemGraph::GetLevelNum() const
{
	int32 Level = 0;
	TArray<UQuestSystemGraphNode*> CurrentLevelNodes = RootNodes;
	TArray<UQuestSystemGraphNode*> NextLevelNodes;

	while(CurrentLevelNodes.Num() != 0)
	{
		for (const auto& CurrentNode : CurrentLevelNodes)
		{
			check(CurrentNode);
			for (const auto& ChildNode : CurrentNode->ChildrenNodes)
			{
				NextLevelNodes.Add(ChildNode);
			}
		}
		CurrentLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
	return Level;
}

void UQuestSystemGraph::GetNodesByLevel(int Level, TArray<UQuestSystemGraphNode*>& Nodes)
{
	int32 CurrentLevelNodes = 0;
	TArray<UQuestSystemGraphNode*> NextLevelNodes;

	Nodes = RootNodes;

	while (Nodes.Num() != 0)
	{
		if (CurrentLevelNodes == Level) break;

		for (const auto& Node : Nodes)
		{
			check(Node);
			for (const auto& ChildNode : Node->ChildrenNodes)
			{
				NextLevelNodes.Add(ChildNode);
			}
		}
		Nodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++CurrentLevelNodes;
	}
}

void UQuestSystemGraph::ClearGraph()
{
	for (const auto& QuestSystemGraphNode : AllNodes)
	{
		if (QuestSystemGraphNode)
		{
			QuestSystemGraphNode->ParentNodes.Empty();
			QuestSystemGraphNode->ChildrenNodes.Empty();
			QuestSystemGraphNode->Edges.Empty();
		}
	}
	AllNodes.Empty();
	RootNodes.Empty();
}
#undef LOCTEXT_NAMESPACE