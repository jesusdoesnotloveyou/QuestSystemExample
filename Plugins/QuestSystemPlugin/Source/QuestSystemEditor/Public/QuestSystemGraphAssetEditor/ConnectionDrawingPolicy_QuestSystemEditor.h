// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ConnectionDrawingPolicy.h"

class UEdGraph;

class QUESTSYSTEMEDITOR_API FConnectionDrawingPolicy_QuestSystemEditor : public FConnectionDrawingPolicy
{
protected:
    UEdGraph* EdGraphObj;
    TMap<UEdGraphNode*, int32> NodeWidgetMap;
public:
	FConnectionDrawingPolicy_QuestSystemEditor(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);
    // FConnectionDrawingPolicy interface
    virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params) override;
    virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget> &InPinGeometries, FArrangedChildren &ArrangedNodes) override;
    virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;
    virtual void DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint, const FConnectionParams& Params) override;
    virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint, const FVector2D& EndPoint, UEdGraphPin* Pin) override;
    virtual FVector2D ComputeSplineTangent(const FVector2D &Start, const FVector2D &End) const override;
    virtual void DetermineLinkGeometry(FArrangedChildren &ArrangedNodes, TSharedRef<SWidget> &OutputPinWidget, UEdGraphPin *OutputPin, UEdGraphPin *InputPin, FArrangedWidget *&StartWidgetGeometry, FArrangedWidget *&EndWidgetGeometry) override;
    virtual void DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params) override;
    // End of FConnectionDrawingPolicy interface
};
