// Quest System by JDNLY. All Rights Reserved

#include "Nodes/QuestSystemGraphNode_Base.h"

#define LOCTEXT_NAMESPACE "QuestSystemGraphNode_Base"

UQuestSystemGraphNode_Base::UQuestSystemGraphNode_Base()
{
#if WITH_EDITORONLY_DATA
    NodeTitle = LOCTEXT("QuestSystemGraphNode_BaseNodeTitle", "Base Node");
    NodeTooltipText = LOCTEXT("QuestSystemGraphNode_BaseTooltip", "The node contains some condition for the next step of a Quest");;
    ContextMenuName = LOCTEXT("QuestSystemGraphNode_BaseContextMenuName", "Base Node");
    BackgroundColor = FLinearColor::Blue;
#endif
}

UQuestSystemGraphNode_Base::~UQuestSystemGraphNode_Base()
{
    
}

FText UQuestSystemGraphNode_Base::GetDescription_Implementation() const
{
    return LOCTEXT("QuestSystemGraphNode_BaseDescription", "Test 0 description");
}

FText UQuestSystemGraphNode_Base::GetNodeCategory_Implementation() const
{
    return Super::GetNodeCategory_Implementation();
}

FText UQuestSystemGraphNode_Base::GetNodeTitle_Implementation() const
{
    return Super::GetNodeTitle_Implementation();
}

// UWorld* UQuestSystemGraphNode_Base::GetWorld(UObject* WorldContextObject) const
// {
//     return WorldContextObject->GetWorld();
// }

#undef LOCTEXT_NAMESPACE