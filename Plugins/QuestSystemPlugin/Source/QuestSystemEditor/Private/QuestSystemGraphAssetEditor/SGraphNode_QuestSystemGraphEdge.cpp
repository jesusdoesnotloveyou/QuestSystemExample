// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/SGraphNode_QuestSystemGraphEdge.h"
#include "QuestSystemGraphAssetEditor/EdNode_QuestSystemGraphEdge.h"

void SGraphNode_QuestSystemGraphEdge::Construct(const FArguments& InArgs, UEdNode_QuestSystemGraphEdge* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

bool SGraphNode_QuestSystemGraphEdge::RequiresSecondPassLayout() const
{
    return true;
}

void SGraphNode_QuestSystemGraphEdge::PerformSecondPassLayout(const TMap<UObject *, TSharedRef<SNode>>& InNodeToWidgetLookup) const
{
    /*UEdNode_QuestSystemGraphEdge* EdgeNode = CastChecked<UEdNode_QuestSystemGraphEdge>(GraphNode);

    FGeometry StartGeometry;
    FGeometry EndGeometry;

    const auto Start = EdgeNode->GetStartNode();
    const auto End = EdgeNode->GetEndNode();
    
    if (Start && End)
    {
        const TSharedRef<SNode>* pFromWidget = InNodeToWidgetLookup.Find(Start);
        const TSharedRef<SNode>* pToWidget = InNodeToWidgetLookup.Find(End);
        if (pFromWidget && pToWidget)
        {
            const TSharedRef<SNode>& FromWidget = *pFromWidget;
            const TSharedRef<SNode>& ToWidget = *pToWidget;

            StartGeometry = FGeometry(FVector2D(Start->NodePosX, Start->NodePosY), FVector2D::ZeroVector, FromWidget->GetDesiredSize(), 1.0f);
            EndGeometry = FGeometry(FVector2D(End->NodePosX, End->NodePosY), FVector2D::ZeroVector, ToWidget->GetDesiredSize(), 1.0f);
        }
    }*/
    
    SGraphNode::PerformSecondPassLayout(InNodeToWidgetLookup);
}

void SGraphNode_QuestSystemGraphEdge::UpdateGraphNode()
{
    /*InputPins.Empty();
    OutputPins.Empty();
	
    // Reset variables that are going to be exposed, in case we are refreshing an already setup node.
    RightNodeBox.Reset();
    LeftNodeBox.Reset();*/
    
    SGraphNode::UpdateGraphNode();
}

// void SGraphNode_QuestSystemGraphEdge::PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const
// {
// }

FSlateColor SGraphNode_QuestSystemGraphEdge::GetEdgeColor() const
{
    return FLinearColor(0.9f, 0.9f, 0.9f, 1.0f );
}
