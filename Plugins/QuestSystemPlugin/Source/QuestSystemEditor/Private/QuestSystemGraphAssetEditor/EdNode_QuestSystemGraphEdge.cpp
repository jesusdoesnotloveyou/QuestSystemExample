// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/EdNode_QuestSystemGraphEdge.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphEdge.h"

UEdNode_QuestSystemGraphEdge::UEdNode_QuestSystemGraphEdge()
{
	
}

UEdNode_QuestSystemGraphEdge::~UEdNode_QuestSystemGraphEdge()
{
	
}

void UEdNode_QuestSystemGraphEdge::SetEdge(UQuestSystemGraphEdge* InEdge)
{
	QuestSystemGraphEdge = InEdge;
}

void UEdNode_QuestSystemGraphEdge::AllocateDefaultPins()
{
	
}

FText UEdNode_QuestSystemGraphEdge::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return QuestSystemGraphEdge ? QuestSystemGraphEdge->GetNodeTitle() : Super::GetNodeTitle(TitleType);
}

void UEdNode_QuestSystemGraphEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	
}

void UEdNode_QuestSystemGraphEdge::PrepareForCopying()
{
	
}

UEdGraphPin* UEdNode_QuestSystemGraphEdge::GetInputPin() const { return Pins[0]; }
UEdGraphPin* UEdNode_QuestSystemGraphEdge::GetOutputPin() const { return Pins[1]; }

void UEdNode_QuestSystemGraphEdge::CreateConnections(UEdGraphNode_QuestSystemGraphNode* Start, UEdGraphNode_QuestSystemGraphNode* End)
{
	
}

UEdGraphNode_QuestSystemGraphNode* UEdNode_QuestSystemGraphEdge::GetStartNode()
{
	return Pins[0]->LinkedTo.Num() > 0 ? Cast<UEdGraphNode_QuestSystemGraphNode>(Pins[0]->LinkedTo[0]->GetOwningNode()) : nullptr;
}

UEdGraphNode_QuestSystemGraphNode* UEdNode_QuestSystemGraphEdge::GetEndNode()
{
	return Pins[1]->LinkedTo.Num() > 0 ? Cast<UEdGraphNode_QuestSystemGraphNode>(Pins[1]->LinkedTo[0]->GetOwningNode()) : nullptr;
}