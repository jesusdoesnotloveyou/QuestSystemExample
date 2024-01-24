// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystemEntities/QSEReachDestinationObjective.h"
#include "QSEBaseCharacter.h"
#include "Triggers/QSETriggerBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEReachDestinationObjective, All, All);

void UQSEReachDestinationObjective::ActivateObjective/*_Implementation*/()
{
	Super::ActivateObjective/*_Implementation*/();
	if(IsActive())
		UE_LOG(LogQSEReachDestinationObjective, Warning, TEXT("ActivateObjective() called for QSEReachDestinationObjective class"));
		
	if (DestinationTrigger)
	{
		DestinationTrigger->OnActorBeginOverlap.AddDynamic(this, &UQSEReachDestinationObjective::OnActorBeginOverlap);
		UE_LOG(LogQSEReachDestinationObjective, Error, TEXT("OnActorBeginOverlap() successfully binded to OnActorBeginOverlap delegate"));
	}
}

bool UQSEReachDestinationObjective::IsComplete() const
{
	return bIsReached;
}

void UQSEReachDestinationObjective::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    const auto PlayerCharacter = Cast<AQSEBaseCharacter>(OtherActor);
    if (!PlayerCharacter) return;
    
	DestinationTrigger->OnActorBeginOverlap.RemoveDynamic(this, &UQSEReachDestinationObjective::OnActorBeginOverlap);
	bIsReached = true;
	
	OnCompletedObjective.Broadcast(this);
    UE_LOG(LogQSEReachDestinationObjective, Error, TEXT("OnCompletedObjective delegate called"));
	
}