// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Nodes/QuestSystemGraphNode.h"
#include "Components/ActorComponent.h"
#include "QuestSystemManagerComponent.generated.h"

class UQuestSystemGraphNode;
class ABaseQuest;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEMRUNTIME_API UQuestSystemManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestSystemManagerComponent();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
    TArray<TSubclassOf<ABaseQuest>> AllQuests;

    TArray<TSubclassOf<ABaseQuest>> CompletedQuests;

    TArray<TSubclassOf<ABaseQuest>> FailedQuests;
    
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
