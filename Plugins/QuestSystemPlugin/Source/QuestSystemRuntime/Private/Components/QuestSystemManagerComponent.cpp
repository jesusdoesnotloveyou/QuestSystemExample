// Quest System by JDNLY. All Rights Reserved

#include "Components/QuestSystemManagerComponent.h"

#include "TimerManager.h"

// Sets default values for this component's properties
UQuestSystemManagerComponent::UQuestSystemManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UQuestSystemManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UQuestSystemManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

