// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "QuestSystemGraphBlueprint.generated.h"

class UQuestSystemGraph;

UCLASS()
class QUESTSYSTEMRUNTIME_API UQuestSystemGraphBlueprint : public UBlueprint
{
	GENERATED_BODY()

public:
    UPROPERTY()
    UQuestSystemGraph* QuestGraph;
    
};