// Quest System by JDNLY. All Rights Reserved

DEFINE_LOG_CATEGORY_STATIC(LogQuestSystemContext, All, All);

#include "Data/QuestSystemContext.h"

UWorld* UQuestSystemContext::GetWorld() const
{
    const auto World = Super::GetWorld();
    if (World)
    {
        UE_LOG(LogQuestSystemContext, Warning, TEXT("World is valid!"));
    }
    return World;
}
