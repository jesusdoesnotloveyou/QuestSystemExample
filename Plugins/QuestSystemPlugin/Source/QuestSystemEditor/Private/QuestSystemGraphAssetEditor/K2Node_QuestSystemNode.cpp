// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/K2Node_QuestSystemNode.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "KismetCompiler.h"

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

    //const auto Node = CompilerContext.SpawnIntermediateNode<UK2Node_QuestSystemNode>(this, SourceGraph);
    //Node->AllocateDefaultPins();
    
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Finally the Node actually works"));

    BreakAllNodeLinks( );
}

FText UK2Node_QuestSystemNode::GetMenuCategory() const
{
    return LOCTEXT("QuestSystemNode_Category", "Quest System");
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
    return LOCTEXT("QuestSystemNode_TooltipText", "Does nothing for now");
}


FText UK2Node_QuestSystemNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    //return UEdGraphNode::GetNodeTitle(ENodeTitleType::EditableTitle);
    return LOCTEXT("QuestSystemNode_NodeTitle", "Base Test Node");
}

FLinearColor UK2Node_QuestSystemNode::GetNodeTitleColor() const
{
    return FLinearColor::Red;
}

#undef LOCTEXT_NAMESPACE