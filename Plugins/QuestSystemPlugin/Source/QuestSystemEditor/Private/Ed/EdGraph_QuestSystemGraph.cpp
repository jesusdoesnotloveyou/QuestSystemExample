// Quest System by JDNLY. All Rights Reserved

#include "Ed/EdGraph_QuestSystemGraph.h"
#include "Ed/EdGraphNode_QuestSystemGraphNode.h"
#include "Ed/EdNode_QuestSystemGraphEdge.h"
#include "Animation/NodeMappingContainer.h"

#include "Graph/QuestSystemGraph.h"
#include "Nodes/QuestSystemGraphNode.h"
#include "Edges/QuestSystemGraphEdge.h"

DEFINE_LOG_CATEGORY_STATIC(LogEdGraph_QuestSystemGraph, All, All);

UEdGraph_QuestSystemGraph::UEdGraph_QuestSystemGraph()
{}

UEdGraph_QuestSystemGraph::~UEdGraph_QuestSystemGraph()
{}

UQuestSystemGraph* UEdGraph_QuestSystemGraph::GetGenericGraph() const
{
    UE_LOG(LogEdGraph_QuestSystemGraph, Warning, TEXT("Outer of EdGraph name: %s"), *GetOuter()->GetName());
	return CastChecked<UQuestSystemGraph>(GetOuter());
}

void UEdGraph_QuestSystemGraph::RebuildGraph()
{
    UE_LOG(LogEdGraph_QuestSystemGraph, Display, TEXT("UEdGraph_QuestSystemGraph::RebuildMounteaDialogueGraph has been called"));

	UQuestSystemGraph* Graph = GetGenericGraph();

	Clear();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdGraphNode_QuestSystemGraphNode* EdNode = Cast<UEdGraphNode_QuestSystemGraphNode>(Nodes[i]))
		{
			if (EdNode->QuestSystemGraphNode == nullptr)
				continue;

			UQuestSystemGraphNode* QuestSystemGraphNode = EdNode->QuestSystemGraphNode;

			NodeMap.Add(QuestSystemGraphNode, EdNode);

			Graph->AllNodes.Add(QuestSystemGraphNode);

			//EdNode->SetDialogueNodeIndex(Graph->AllNodes.Find(EdNode->DialogueGraphNode));

			for (int PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
			{
				UEdGraphPin* Pin = EdNode->Pins[PinIdx];

				if (Pin->Direction != EGPD_Output)
					continue;

				for (int LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
				{
					UQuestSystemGraphNode* ChildNode = nullptr;
					if (UEdGraphNode_QuestSystemGraphNode* EdNode_Child = Cast<UEdGraphNode_QuestSystemGraphNode>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						ChildNode = EdNode_Child->QuestSystemGraphNode;
					}
					else if (UEdNode_QuestSystemGraphEdge* EdNode_Edge = Cast<UEdNode_QuestSystemGraphEdge>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						UEdGraphNode_QuestSystemGraphNode* Child = EdNode_Edge->GetEndNode();;
						if (Child != nullptr)
						{
							ChildNode = Child->QuestSystemGraphNode;
						}
					}

					if (ChildNode != nullptr)
					{
						QuestSystemGraphNode->ChildrenNodes.Add(ChildNode);

						ChildNode->ParentNodes.Add(QuestSystemGraphNode);
					}
					else
					{
						UE_LOG(LogEdGraph_QuestSystemGraph, Error, TEXT("[RebuildGraph] Can't find child node."));
					}
				}
			}
		}
		else if (UEdNode_QuestSystemGraphEdge* EdgeNode = Cast<UEdNode_QuestSystemGraphEdge>(Nodes[i]))
		{
			UEdGraphNode_QuestSystemGraphNode* StartNode = EdgeNode->GetStartNode();
			UEdGraphNode_QuestSystemGraphNode* EndNode = EdgeNode->GetEndNode();
			UQuestSystemGraphEdge* Edge = EdgeNode->QuestSystemGraphEdge;

			if (StartNode == nullptr || EndNode == nullptr || Edge == nullptr)
			{
			    UE_LOG(LogEdGraph_QuestSystemGraph, Error, TEXT("[RebuildGraph] Add edge failed."));
				continue;
			}

			EdgeMap.Add(Edge, EdgeNode);

			Edge->Graph = Graph;
			Edge->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
			Edge->StartNode = StartNode->QuestSystemGraphNode;
			Edge->EndNode = EndNode->QuestSystemGraphNode;
			Edge->StartNode->Edges.Add(Edge->EndNode, Edge);
		}
	}

	for (int i = 0; i < Graph->AllNodes.Num(); ++i)
	{
		UQuestSystemGraphNode* Node = Graph->AllNodes[i];
		if (Node->ParentNodes.Num() == 0)
		{
			Graph->RootNodes.Add(Node);

			SortNodes(Node);
		}

		Node->Graph = Graph;
		Node->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
	}

	Graph->RootNodes.Sort([&](const UQuestSystemGraphNode& L, const UQuestSystemGraphNode& R)
	{
		/*const*/ UEdGraphNode_QuestSystemGraphNode* EdNode_LNode = NodeMap[&L];
		/*const*/ UEdGraphNode_QuestSystemGraphNode* EdNode_RNode = NodeMap[&R];
		return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
	});
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
	EdgeMap.Reset();

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
    int Level = 0;
    TArray<UQuestSystemGraphNode*> CurrLevelNodes = { RootNode };
    TArray<UQuestSystemGraphNode*> NextLevelNodes;

    while (CurrLevelNodes.Num() != 0)
    {
        int32 LevelWidth = 0;
        for (int i = 0; i < CurrLevelNodes.Num(); ++i)
        {
            UQuestSystemGraphNode* Node = CurrLevelNodes[i];

            auto Comp = [&](const UQuestSystemGraphNode& L, const UQuestSystemGraphNode& R)
            {
                UEdGraphNode_QuestSystemGraphNode* EdNode_LNode = NodeMap[&L];
                UEdGraphNode_QuestSystemGraphNode* EdNode_RNode = NodeMap[&R];
                return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
            };

            Node->ChildrenNodes.Sort(Comp);
            Node->ParentNodes.Sort(Comp);
            
            for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
            {
                NextLevelNodes.Add(Node->ChildrenNodes[j]);
            }
        }

        CurrLevelNodes = NextLevelNodes;
        NextLevelNodes.Reset();
        ++Level;
    }
}

void UEdGraph_QuestSystemGraph::PostEditUndo()
{
    NotifyGraphChanged();
    Super::PostEditUndo();
}