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

    // Allow to make all this actions with node in the editor        
    bAllowCopy = true;
    bAllowDelete = true;
    bAllowDuplicate = true;
    bAllowPaste = true;
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

// TODO: these four functions below might need overriding more complex than these 
bool UEdGraphNode_QuestSystemGraphNode::CanUserCopyNodes() const
{
    return bAllowCopy;
}

bool UEdGraphNode_QuestSystemGraphNode::CanUserDeleteNode() const
{
    if (!Super::CanUserDeleteNode()) return false;
    return bAllowDelete;
}

bool UEdGraphNode_QuestSystemGraphNode::CanDuplicateNode() const
{
    if (!Super::CanDuplicateNode()) return false;
    return bAllowDuplicate;
}

bool UEdGraphNode_QuestSystemGraphNode::CanUserPasteNodes() const
{
    return bAllowPaste;
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
	return FText(FText::FromString(("QuestSystemGraphNode isn't valid")));
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
	Super::PostEditUndo();
}

void UEdGraphNode_QuestSystemGraphNode::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
}