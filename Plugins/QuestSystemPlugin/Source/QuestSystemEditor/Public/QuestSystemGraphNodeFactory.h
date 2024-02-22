// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"
#include "EdGraph/EdGraphNode.h"

struct QUESTSYSTEMEDITOR_API FQuestSystemGraphNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};

struct QUESTSYSTEMEDITOR_API FQuestSystemGraphNodePinFactory : public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;
};

struct QUESTSYSTEMEDITOR_API FQuestSystemGraphPinConnectionFactory : public FGraphPanelPinConnectionFactory
{
public:
    virtual class FConnectionDrawingPolicy* CreateConnectionPolicy(const class UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const class FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;
};