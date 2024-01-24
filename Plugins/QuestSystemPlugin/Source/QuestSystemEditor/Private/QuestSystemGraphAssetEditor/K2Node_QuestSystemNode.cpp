// Quest System by JDNLY. All Rights Reserved


#include "QuestSystemGraphAssetEditor/K2Node_QuestSystemNode.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

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

FText UK2Node_QuestSystemNode::GetMenuCategory() const
{
    return Super::GetMenuCategory();
}

/////////////////////////////////////////////////////
// UEdGraphNode
FLinearColor UK2Node_QuestSystemNode::GetNodeTitleColor() const
{
    return FLinearColor::Red;
}

FText UK2Node_QuestSystemNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return UEdGraphNode::GetNodeTitle(ENodeTitleType::EditableTitle);
}