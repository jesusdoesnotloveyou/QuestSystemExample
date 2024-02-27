// Quest System by JDNLY. All Rights Reserved

#include "Nodes/QuestSystemGraphNode_Base.h"

UQuestSystemGraphNode_Base::UQuestSystemGraphNode_Base()
{
#if WITH_EDITORONLY_DATA
    BackgroundColor = FLinearColor::Blue;
#endif
}

UQuestSystemGraphNode_Base::~UQuestSystemGraphNode_Base()
{
    
}

FText UQuestSystemGraphNode_Base::GetDescription_Implementation() const
{
    return Super::GetDescription_Implementation();
}

FText UQuestSystemGraphNode_Base::GetNodeCategory_Implementation() const
{
    return Super::GetNodeCategory_Implementation();
}

FText UQuestSystemGraphNode_Base::GetNodeTitle_Implementation() const
{
    return Super::GetNodeTitle_Implementation();
}