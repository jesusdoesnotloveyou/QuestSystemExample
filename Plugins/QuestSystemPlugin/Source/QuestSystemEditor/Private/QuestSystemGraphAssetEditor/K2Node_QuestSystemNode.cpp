// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/K2Node_QuestSystemNode.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

#define LOCTEXT_NAMESPACE "UK2Node_QuestSystemNode"

/////////////////////////////////////////////////////
// UK2Node
void UK2Node_QuestSystemNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    const UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        check(NodeSpawner);

        ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
    }
}
void UK2Node_QuestSystemNode::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Finally the Node actually works"));
}

FText UK2Node_QuestSystemNode::GetMenuCategory() const
{
    return LOCTEXT("K2Node_QuestSystem_Category", "Quest System");
}

/////////////////////////////////////////////////////
// UEdGraphNode

const FName UK2Node_QuestSystemNode::NAME_ObjectToCheck = ( TEXT("ObjectToCheck") );
const FName UK2Node_QuestSystemNode::NAME_IsValidCheck = ( TEXT("ObjectToCheck") );
const FName UK2Node_QuestSystemNode::NAME_IsNotValidCheck = ( TEXT("ObjectToCheck") );

void UK2Node_QuestSystemNode::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), NAME_ObjectToCheck);
    
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NAME_IsValidCheck);

    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NAME_IsNotValidCheck);
}

FText UK2Node_QuestSystemNode::GetTooltipText() const
{
    return LOCTEXT("K2Node_QuestSystem_TooltipText", "Does nothing for now");
}

FLinearColor UK2Node_QuestSystemNode::GetNodeTitleColor() const
{
    return FLinearColor::Red;
}

FText UK2Node_QuestSystemNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    //return UEdGraphNode::GetNodeTitle(ENodeTitleType::EditableTitle);
    return LOCTEXT("K2Node_QuestSystem_NodeTitle", "Test Node");
}

#undef LOCTEXT_NAMESPACE