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
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, FName(), TEXT("In"));
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, FName(), TEXT("Out"));
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

// TODO: two functions below might need overriding more complex than these 
bool UEdGraphNode_QuestSystemGraphNode::CanUserDeleteNode() const
{
    return Super::CanUserDeleteNode();
}

bool UEdGraphNode_QuestSystemGraphNode::CanDuplicateNode() const
{
    return Super::CanDuplicateNode();
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
    if (QuestSystemGraphNode)
    {
        return QuestSystemGraphNode->GetNodeTooltipText();
    }
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