// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystemContext.generated.h"

/**
 * Quest Context
 *
 * Contains information needed to successfully using quest at runtime 
 * 
 */
 
UCLASS()
class QUESTSYSTEMRUNTIME_API UQuestSystemContext : public UObject
{
	GENERATED_BODY()

public:
    virtual UWorld* GetWorld() const override;

    UPROPERTY(BlueprintReadWrite, Category = "Quest Context")
    TArray<TSubclassOf<APawn>> QuestParticipants;

    UPROPERTY(BlueprintReadWrite, Category = "Quest Context")
    TArray<UObject*> ObjectForQuest;
};
