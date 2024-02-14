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

    static const FName NAME_ObjectToCheck;
    static const FName NAME_IsValidCheck;
    static const FName NAME_IsNotValidCheck;
    
public:
    // UK2Node interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    
    virtual FText GetMenuCategory() const override;
    
    //Expands a node while compiling, which may add additional nodes or delete this node.
    virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);

    virtual bool IsNodeSafeToIgnore() const { return true; }
    
    // End of UK2Node interface
    
    // UEdGraphNode interface
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

    //Gets the tooltip that will be shown when the node is hovered
    virtual FText GetTooltipText() const;

    virtual void AllocateDefaultPins() override;
    // End of UEdGraphNode interface
};
