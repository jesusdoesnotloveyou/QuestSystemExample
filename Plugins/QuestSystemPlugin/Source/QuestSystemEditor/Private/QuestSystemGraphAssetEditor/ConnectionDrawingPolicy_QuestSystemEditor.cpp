// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/ConnectionDrawingPolicy_QuestSystemEditor.h"

#include "Ed/EdGraphNode_QuestSystemGraphNode.h"
#include "Ed/EdNode_QuestSystemGraphEdge.h"

FConnectionDrawingPolicy_QuestSystemEditor::FConnectionDrawingPolicy_QuestSystemEditor(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj)
    : FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements)
    , EdGraphObj(InGraphObj) { }

/** Give specific editor modes a chance to highlight this connection or darken non-interesting connections */
void FConnectionDrawingPolicy_QuestSystemEditor::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params)
{
    Params.AssociatedPin1 = OutputPin;
    Params.AssociatedPin2 = InputPin;
    Params.WireThickness = 1.5f;

    const bool bDeemphasizeUnhoveredPins = HoveredPins.Num() > 0;
    if (bDeemphasizeUnhoveredPins)
    {
    	ApplyHoverDeemphasis(OutputPin, InputPin, /*inout*/ Params.WireThickness, /*inout*/ Params.WireColor);
    }
}

void FConnectionDrawingPolicy_QuestSystemEditor::Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes)
{
    NodeWidgetMap.Empty();
    for (int32 NodeIndex = 0; NodeIndex < ArrangedNodes.Num(); ++NodeIndex)
    {
        FArrangedWidget& CurWidget = ArrangedNodes[NodeIndex];
        TSharedRef<SGraphNode> ChildNode = StaticCastSharedRef<SGraphNode>(CurWidget.Widget);
        NodeWidgetMap.Add(ChildNode->GetNodeObj(), NodeIndex);
    }
    
    FConnectionDrawingPolicy::Draw(InPinGeometries, ArrangedNodes);
}

void FConnectionDrawingPolicy_QuestSystemEditor::DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params)
{
    FConnectionDrawingPolicy::DrawSplineWithArrow(StartGeom, EndGeom, Params);
}

void FConnectionDrawingPolicy_QuestSystemEditor::DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint, const FConnectionParams& Params)
{
    FConnectionDrawingPolicy::DrawSplineWithArrow(StartPoint, EndPoint, Params);
}

void FConnectionDrawingPolicy_QuestSystemEditor::DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint, const FVector2D& EndPoint, UEdGraphPin* Pin)
{
    FConnectionParams Params;
    DetermineWiringStyle(Pin, nullptr, /*inout*/ Params);

    if (Pin->Direction == EGPD_Output)
    {
        DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, EndPoint), EndPoint, Params);
    }
    else
    {
        DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, StartPoint), StartPoint, Params);
    }
}

FVector2D FConnectionDrawingPolicy_QuestSystemEditor::ComputeSplineTangent(const FVector2D &Start, const FVector2D &End) const
{
    const FVector2D Delta = End - Start;
    const FVector2D NormDelta = Delta.GetSafeNormal();

    return NormDelta;
}

void FConnectionDrawingPolicy_QuestSystemEditor::DetermineLinkGeometry(
    FArrangedChildren &ArrangedNodes,
    TSharedRef<SWidget> &OutputPinWidget,
    UEdGraphPin *OutputPin,
    UEdGraphPin *InputPin,
    FArrangedWidget *&StartWidgetGeometry,
    FArrangedWidget *&EndWidgetGeometry)
{
    if (UEdNode_QuestSystemGraphEdge* EdgeNode = Cast<UEdNode_QuestSystemGraphEdge>(InputPin->GetOwningNode()))
    	{
    		UEdGraphNode_QuestSystemGraphNode* Start = EdgeNode->GetStartNode();
    		UEdGraphNode_QuestSystemGraphNode* End = EdgeNode->GetEndNode();
    		if (Start != nullptr && End != nullptr)
    		{
    			int32* StartNodeIndex = NodeWidgetMap.Find(Start);
    			int32* EndNodeIndex = NodeWidgetMap.Find(End);
    			if (StartNodeIndex && EndNodeIndex)
    			{
    				StartWidgetGeometry = &(ArrangedNodes[*StartNodeIndex]);
    				EndWidgetGeometry = &(ArrangedNodes[*EndNodeIndex]);
    			}
    		}
    	}
    	else
    	{
    		StartWidgetGeometry = PinGeometries->Find(OutputPinWidget);
    
    		if (TSharedPtr<SGraphPin>* pTargetWidget = PinToPinWidgetMap.Find(InputPin))
    		{
    			TSharedRef<SGraphPin> InputWidget = (*pTargetWidget).ToSharedRef();
    			EndWidgetGeometry = PinGeometries->Find(InputWidget);
    		}
    	}
}

void FConnectionDrawingPolicy_QuestSystemEditor::DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params)
{
    FConnectionDrawingPolicy::DrawConnection(LayerId, Start, End, Params);
}