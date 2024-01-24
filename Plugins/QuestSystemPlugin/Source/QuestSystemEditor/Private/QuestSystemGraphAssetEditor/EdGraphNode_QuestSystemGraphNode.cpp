// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdGraph_QuestSystemGraph.h"
#include "QuestSystemGraphAssetEditor/AssetQuestSystemGraphSchema.h"
#include "QuestSystemGraphNode.h"

UEdGraphNode_QuestSystemGraphNode::UEdGraphNode_QuestSystemGraphNode()
{
	bCanRenameNode = true;
	bCanResizeNode = true;
	bHasCompilerMessage = false;
}

UEdGraphNode_QuestSystemGraphNode::~UEdGraphNode_QuestSystemGraphNode()
{
	
}

void UEdGraphNode_QuestSystemGraphNode::SetQuestSystemGraphNode(UQuestSystemGraphNode* InNode)
{
	QuestSystemGraphNode = InNode;
}

void UEdGraphNode_QuestSystemGraphNode::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();
	// TO DO: find out how CreatePin method works
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

void UEdGraphNode_QuestSystemGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin)
	{
		if (GetSchema()->TryCreateConnection(FromPin, FromPin->Direction == EGPD_Input ? GetOutputPin() : GetInputPin()))
		{
		    // Need to overload NodeConnectionListChanged cause it's empty in UEdGraphNode
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

void UEdGraphNode_QuestSystemGraphNode::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();
}

UEdGraph_QuestSystemGraph* UEdGraphNode_QuestSystemGraphNode::GetEdGraph() const
{
	return CastChecked<UEdGraph_QuestSystemGraph>(GetGraph());
}

FText UEdGraphNode_QuestSystemGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return QuestSystemGraphNode ? QuestSystemGraphNode->NodeTitle : Super::GetNodeTitle(TitleType);
}

FText UEdGraphNode_QuestSystemGraphNode::GetTooltipText() const
{
	return FText();
}

UEdGraphPin* UEdGraphNode_QuestSystemGraphNode::GetInputPin() const
{
	return Pins[0];
}

UEdGraphPin* UEdGraphNode_QuestSystemGraphNode::GetOutputPin() const
{
	return Pins[1];
}

void UEdGraphNode_QuestSystemGraphNode::PostEditUndo()
{
	UEdGraphNode::PostEditUndo();
}