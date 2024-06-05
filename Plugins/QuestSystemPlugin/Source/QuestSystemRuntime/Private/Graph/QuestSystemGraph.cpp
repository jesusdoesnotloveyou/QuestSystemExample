// Quest System by JDNLY. All Rights Reserved

#include "Graph/QuestSystemGraph.h"
#include "Engine/Engine.h"
#include "Nodes/QuestSystemGraphNode.h"
#include "Edges/QuestSystemGraphEdge.h"
#include "Data/QuestSystemContext.h"
#include "Nodes/QuestSystemGraphNode_Base.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestSystemGraph, All, All);

#define LOCTEXT_NAMESPACE "QuestSystemGraph"

UQuestSystemGraph::UQuestSystemGraph()
{   
	NodeType = UQuestSystemGraphNode::StaticClass();
	EdgeType = UQuestSystemGraphEdge::StaticClass();

    GraphGUID = FGuid::NewGuid();
	bEdgeEnabled = true;


#if WITH_EDITORONLY_DATA
    Context = nullptr;
	EdGraph = nullptr;
	bCanRenameNode = true;
	
#endif
}

UQuestSystemGraph::~UQuestSystemGraph()
{
	
}

UQuestSystemGraphNode* UQuestSystemGraph::GetStartNode() const
{
    return StartNode;
}

TArray<UQuestSystemGraphNode*> UQuestSystemGraph::GetRootNodes() const
{
    return RootNodes;
}
    
TArray<UQuestSystemGraphNode*> UQuestSystemGraph::GetAllNodes() const
{
    return AllNodes;
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

void UQuestSystemGraph::CreateGraph()
{
#if WITH_EDITOR
    // EdGraph already exists
    if (EdGraph) return;

    // Start node already exists
    if (StartNode) return;

    StartNode = ConstructQuestSystemNode<UQuestSystemGraphNode_Base>();
    if (StartNode)
    {
        StartNode->Graph = this;
        RootNodes.Add(StartNode);
        AllNodes.Add(StartNode);    
    }
#endif
}

void UQuestSystemGraph::ClearGraph()
{
	for (const auto& Node : AllNodes)
	{
		if (Node)
		{
			Node->ParentNodes.Empty();
			Node->ChildrenNodes.Empty();
			Node->Edges.Empty();
		}
	}
	AllNodes.Empty();
	RootNodes.Empty();
}
#undef LOCTEXT_NAMESPACE