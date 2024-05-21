// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphNode.h"
#include "QuestSystemGraph.h"
#include "Chaos/SAT.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestSystemGraphNode, All, All);
DECLARE_LOG_CATEGORY_EXTERN(LogQuestSystemGraphNodeTestExtern, Warning, All);

#define LOCTEXT_NAMESPACE "QuestSystemGraphNode"

UQuestSystemGraphNode::UQuestSystemGraphNode()
{
    UE_LOG(LogQuestSystemGraphNode, Error, TEXT("Test message for plugin log category"));
    NodeGUID = FGuid::NewGuid();

#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UQuestSystemGraph::StaticClass();
	BackgroundColor = FLinearColor::Black;
#endif
}
UQuestSystemGraphNode::~UQuestSystemGraphNode()
{
	
}

UQuestSystemGraphEdge* UQuestSystemGraphNode::GetEdge(UQuestSystemGraphNode* ChildNode)
{
	return Edges.Contains(ChildNode) ? Edges.FindChecked(ChildNode) : nullptr;
}

UQuestSystemGraph* UQuestSystemGraphNode::GetGraph() const
{
	return Graph;
}

bool UQuestSystemGraphNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

UWorld* UQuestSystemGraphNode::GetWorld() const
{
    if (OwningWorld) return OwningWorld;

    // Might need to make separate function for getting Level
    const ULevel* Level = GetTypedOuter<ULevel>();
    //~
    if (Level) return Level->GetWorld();
    return nullptr;
}

FText UQuestSystemGraphNode::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Quest System Graph Node");
}

FText UQuestSystemGraphNode::GetNodeCategory_Implementation() const
{
    return LOCTEXT("NodeCategory", "Quest System Base Graph Node");
}

FText UQuestSystemGraphNode::GetNodeTooltipText_Implementation() const
{
    return NodeTooltipText;
}

FText UQuestSystemGraphNode::GetNodeTitle_Implementation() const
{
	return NodeTitle.IsEmpty() ? GetDescription() : NodeTitle;
}

void UQuestSystemGraphNode::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}

bool UQuestSystemGraphNode::IsNameEditable() const
{
	return true;
}

FLinearColor UQuestSystemGraphNode::GetBackgroundColor() const
{
	return BackgroundColor;
}

bool UQuestSystemGraphNode::CanCreateConnection(UQuestSystemGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

bool UQuestSystemGraphNode::CanCreateConnectionTo(UQuestSystemGraphNode* Other, int32 NumberOfChildrenNodes,
	FText& ErrorMessage)
{
	if (NumberOfChildrenNodes >= ChildrenLimit && ChildrenLimitType == ENodeLimit::Limited)
	{
		ErrorMessage = FText::FromString("Children limit exceeded");
		return false;
	}
	return CanCreateConnection(Other, ErrorMessage);
}

bool UQuestSystemGraphNode::CanCreateConnectionFrom(UQuestSystemGraphNode* Other, int32 NumberOfParentNodes,
	FText& ErrorMessage)
{
	if (ParentLimitType == ENodeLimit::Limited && NumberOfParentNodes >= ParentLimit)
	{
		ErrorMessage = FText::FromString("Parent limit exceeded");
		return false;
	}
	return true;
}

#undef LOCTEXT_NAMESPACE
