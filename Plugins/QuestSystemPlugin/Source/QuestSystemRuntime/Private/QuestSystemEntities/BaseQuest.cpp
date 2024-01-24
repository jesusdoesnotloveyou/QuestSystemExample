// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemEntities/BaseQuest.h"
#include "GameFramework/Character.h"
#include "Components/BillboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseQuest, All, All);

ABaseQuest::ABaseQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	QuestSpriteIcon = CreateDefaultSubobject<UBillboardComponent>("QuestSpriteIcon");
	LogicCollisionComponent = CreateDefaultSubobject<USphereComponent>("LogicCollisionComponent");
	LogicCollisionComponent->InitSphereRadius(50.0f);
	LogicCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LogicCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(QuestSpriteIcon);
	LogicCollisionComponent->SetupAttachment(GetRootComponent());
}

TArray<TSubclassOf<UBaseObjective>>& ABaseQuest::GetObjectives()
{
	return Objectives;
}

// Called when the game starts or when spawned
void ABaseQuest::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseQuest::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;

	UE_LOG(LogBaseQuest, Warning, TEXT("Quest restrictor has been overlaped by %s"), *Character->GetName());
}

//EQuestState ABaseQuest::GetQuestState() const
//{
//	return QuestState;
//}
