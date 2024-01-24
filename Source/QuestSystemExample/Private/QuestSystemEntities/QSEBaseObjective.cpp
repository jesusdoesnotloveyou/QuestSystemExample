// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystemEntities/QSEBaseObjective.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEBaseObjective, All, All);

void UQSEBaseObjective::ActivateObjective/*_Implementation*/()
{
	bIsActive = true;
    OnCompletedObjective.AddDynamic(this, &UQSEBaseObjective::OnCompletedObjective_1);
    UE_LOG(LogQSEBaseObjective, Error, TEXT("OnCompletedObjective() is binded"));
}

void UQSEBaseObjective::OnCompletedObjective_1(UQSEBaseObjective* Objective)
{
    // Should change bIsCompleted here
    if (Objective) UE_LOG(LogQSEBaseObjective, Error, TEXT("Objective is valid, name: %s"), *Objective->GetName());
    UE_LOG(LogQSEBaseObjective, Error, TEXT("OnCompletedObjective() called"));
    OnCompletedObjective.RemoveDynamic(Objective, &UQSEBaseObjective::OnCompletedObjective_1);
    OnActivateObjective.Broadcast();
}