// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemEntities/QSETravelQuest.h"
#include "QSEObjectiveCollection.h"
#include "QSEReachDestinationObjective.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSETravelQuest, All, All);

void AQSETravelQuest::BeginPlay()
{
	Super::BeginPlay();
	RootObjectiveCollection = CreateRootObjectiveCollection();
	RootObjectiveCollection->ActivateObjective();
}

UQSEObjectiveCollection* AQSETravelQuest::CreateRootObjectiveCollection()
{
	UE_LOG(LogQSETravelQuest, Warning, TEXT("CreateRootObjectiveCollection() called for derived class"));
	RootObjectiveCollection = NewObject<UQSEObjectiveCollection>(this, TEXT("Journey to Novigrad"));
	PopulateObjectives(RootObjectiveCollection);
	return RootObjectiveCollection;
}

void AQSETravelQuest::PopulateObjectives(UQSEObjectiveCollection* RootCollection)
{
	auto Objective = NewObject<UQSEReachDestinationObjective>(this, TEXT("Bridge across Pontar"));
    Objective->DestinationTrigger = TravelQuestTriggers[0];
	RootCollection->AddObjective(Cast<UQSEBaseObjective>(Objective));

    Objective = NewObject<UQSEReachDestinationObjective>(this, TEXT("Cross the river"));
    Objective->DestinationTrigger = TravelQuestTriggers[1];
    RootCollection->AddObjective(Cast<UQSEBaseObjective>(Objective));

    Objective = NewObject<UQSEReachDestinationObjective>(this, TEXT("Get to Novigrad"));
    Objective->DestinationTrigger = TravelQuestTriggers[2];
    RootCollection->AddObjective(Cast<UQSEBaseObjective>(Objective));
}



