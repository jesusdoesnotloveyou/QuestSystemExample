// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_QuestSystemNode.generated.h"

class FBlueprintActionDatabaseRegistrar;

UCLASS()
class QUESTSYSTEMEDITOR_API UK2Node_QuestSystemNode : public UK2Node
{
	GENERATED_BODY()

public:
    // K2Node interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
    // End of K2Node interface
    
    // EdGraphNode interface
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    // End of EdGraphNode interface
};
