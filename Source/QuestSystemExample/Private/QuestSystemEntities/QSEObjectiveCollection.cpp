// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystemEntities/QSEObjectiveCollection.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEObjectiveCollection, All, All);

UQSEObjectiveCollection::UQSEObjectiveCollection()
{
}

void UQSEObjectiveCollection::ActivateObjective/*_Implementation*/()
{
    bIsActive = true;
    bIsOrderRequired = false;
    Super::OnActivateObjective.AddDynamic(this, &UQSEObjectiveCollection::OnActivateObjective);
	OnActivateObjective();
}

void UQSEObjectiveCollection::OnActivateObjective()
{
	if (bIsOrderRequired)
	{
	    const auto NextIncompleteObjective = FindNextIncompleteObjective();
	    if (!NextIncompleteObjective) return;
	    //TODO: logic of completing the entire quest and setting it as completed in the quest manager
	    
	    NextIncompleteObjective->ActivateObjective();
	}
	else
	{
		for (const auto Objective : Objectives)
		{
			if (!Objective) continue;
			Objective->ActivateObjective();
		}
	}
}

void UQSEObjectiveCollection::ContinueActivatingObjectives()
{
    
}

// TODO: check the method
UQSEBaseObjective* UQSEObjectiveCollection::FindNextIncompleteObjective()
{
	for (const auto Objective : Objectives)
	{
		if (!Objective) continue;
		if (!Objective->IsComplete()) return Objective;
	}
	return nullptr;
}

// TODO: check the method
bool UQSEObjectiveCollection::IsComplete() const
{
	for (const auto Objective : Objectives)
	{
		// Might be bad decision
		if (!Objective) continue;
		if (!Objective->IsComplete()) return false;
	}
	return true;
}

void UQSEObjectiveCollection::AddObjective(UQSEBaseObjective* NewObjective)
{
	if (!NewObjective) return;
	Objectives.Add(NewObjective);
	UE_LOG(LogQSEObjectiveCollection, Warning, TEXT("Objective added to objectives array"));
}