// Fill out your copyright notice in the Description page of Project Settings.


#include "QSEBaseQuest.h"
#include "QSEObjectiveCollection.h"
#include "QSEBaseObjective.h"
#include "Player/QSEBaseCharacter.h"
#include "Components/BillboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEBaseQuest, All, All);

AQSEBaseQuest::AQSEBaseQuest()
{
	PrimaryActorTick.bCanEverTick = false;

	QuestSpriteIcon = CreateDefaultSubobject<UBillboardComponent>("QuestSpriteIcon");
	QuestSpriteIcon->bHiddenInGame = false;
	LogicCollisionComponent = CreateDefaultSubobject<USphereComponent>("LogicCollisionComponent");
	LogicCollisionComponent->InitSphereRadius(50.0f);
	LogicCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LogicCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(QuestSpriteIcon);
	LogicCollisionComponent->SetupAttachment(GetRootComponent());
}

void AQSEBaseQuest::BeginPlay()
{
	Super::BeginPlay();
}

UQSEObjectiveCollection* AQSEBaseQuest::GetRootObjectiveCollection() const
{
	return RootObjectiveCollection; 
}

UQSEObjectiveCollection* AQSEBaseQuest::CreateRootObjectiveCollection() { return nullptr; }

void AQSEBaseQuest::PopulateObjectives(UQSEObjectiveCollection* RootCollection) { }

void AQSEBaseQuest::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	const auto PlayerCharacter = Cast<AQSEBaseCharacter>(OtherActor);
	if (!PlayerCharacter) return;

	if (QuestState == EQSEQuestState::WaitingToStart)
	{
		SetQuestState(EQSEQuestState::InProgress);
		UE_LOG(LogQSEBaseQuest, Warning, TEXT("Quest started by player character: %s"), *PlayerCharacter->GetName());
	}
}

void AQSEBaseQuest::SetQuestState(EQSEQuestState State)
{
	if (QuestState == State) return;
	QuestState = State;
}

