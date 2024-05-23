// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

// Forward declarations
class UEdGraphNode_QuestSystemGraphNode;
class UK2Node_QuestSystemNode;
struct FSlateBrush;

class QUESTSYSTEMEDITOR_API SGraphNode_QuestSystemGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_QuestSystemGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphNode_QuestSystemGraphNode* InNode);

    // SGraphNode interface
    virtual void UpdateGraphNode() override;
    virtual void CreatePinWidgets() override;
    virtual void AddPin(const TSharedRef<SGraphPin> &PinToAdd) override;
    virtual bool IsNameReadOnly() const;
    // End of SGraphNode interface

    virtual FSlateColor GetBorderBackgroundColor() const;
    
    virtual FSlateColor GetBackgroundColor() const;

    virtual EVisibility GetGragOverMarkerVisibility();
    
    virtual const FSlateBrush* GetNameIcon() const;

    
    
};