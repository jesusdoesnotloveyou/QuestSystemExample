// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/EdNodeEdge_QuestSystemGraphEdge.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphEdge.h"

UEdNodeEdge_QuestSystemGraphEdge::UEdNodeEdge_QuestSystemGraphEdge()
{
	
}

UEdNodeEdge_QuestSystemGraphEdge::~UEdNodeEdge_QuestSystemGraphEdge()
{
	
}

void UEdNodeEdge_QuestSystemGraphEdge::SetEdge(UQuestSystemGraphEdge* InEdge)
{
	QuestSystemGraphEdge = InEdge;
}

void UEdNodeEdge_QuestSystemGraphEdge::AllocateDefaultPins()
{
	
}

FText UEdNodeEdge_QuestSystemGraphEdge::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return QuestSystemGraphEdge ? QuestSystemGraphEdge->GetNodeTitle() : Super::GetNodeTitle(TitleType);
}

void UEdNodeEdge_QuestSystemGraphEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	
}

void UEdNodeEdge_QuestSystemGraphEdge::PrepareForCopying()
{
	
}

UEdGraphPin* UEdNodeEdge_QuestSystemGraphEdge::GetInputPin() const { return Pins[0]; }
UEdGraphPin* UEdNodeEdge_QuestSystemGraphEdge::GetOutputPin() const { return Pins[1]; }

void UEdNodeEdge_QuestSystemGraphEdge::CreateConnections(UEdGraphNode_QuestSystemGraphNode* Start, UEdGraphNode_QuestSystemGraphNode* End)
{
	
}

UEdGraphNode_QuestSystemGraphNode* UEdNodeEdge_QuestSystemGraphEdge::GetStartNode()
{
	return Pins[0]->LinkedTo.Num() > 0 ? Cast<UEdGraphNode_QuestSystemGraphNode>(Pins[0]->LinkedTo[0]->GetOwningNode()) : nullptr;
}

UEdGraphNode_QuestSystemGraphNode* UEdNodeEdge_QuestSystemGraphEdge::GetEndNode()
{
	return Pins[1]->LinkedTo.Num() > 0 ? Cast<UEdGraphNode_QuestSystemGraphNode>(Pins[1]->LinkedTo[0]->GetOwningNode()) : nullptr;
}