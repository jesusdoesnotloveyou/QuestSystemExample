// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystemEntities/QSEBaseObjective.h"
#include "QSEReachDestinationObjective.generated.h"

class ATriggerBase;

UCLASS()
class QUESTSYSTEMEXAMPLE_API UQSEReachDestinationObjective : public UQSEBaseObjective
{
	GENERATED_BODY()
public:
	UPROPERTY()
	ATriggerBase* DestinationTrigger;
public:
	virtual bool IsComplete() const override;
	
	virtual void ActivateObjective/*_Implementation*/() override;
private:
	bool bIsReached = false;

    UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
