// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystemEntities/QSEBaseQuest.h"
#include "QSETravelQuest.generated.h"

class ATriggerBase;
class AQSETriggerBase;

UCLASS()
class QUESTSYSTEMEXAMPLE_API AQSETravelQuest : public AQSEBaseQuest
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggers")
    TArray<ATriggerBase*> TravelQuestTriggers;
    
protected:
	virtual UQSEObjectiveCollection* CreateRootObjectiveCollection() override;
	virtual void PopulateObjectives(UQSEObjectiveCollection* RootCollection) override;

	virtual void BeginPlay() override;
};
