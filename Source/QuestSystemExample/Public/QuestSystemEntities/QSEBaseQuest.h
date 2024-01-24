// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "Misc/Guid.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "QSECoreTypes.h"
#include "QSEBaseQuest.generated.h"

class UQSEBaseObjective;
class UQSEObjectiveCollection;
class USphereComponent;
class UBillboardComponent;

UCLASS(Abstract)
class QUESTSYSTEMEXAMPLE_API AQSEBaseQuest : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	UBillboardComponent* QuestSpriteIcon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
	USphereComponent* LogicCollisionComponent;

	UPROPERTY(/*EditAnywhere, BlueprintReadWrite, Category="ObjectiveCollection"*/)
	UQSEObjectiveCollection* RootObjectiveCollection;
public:
	AQSEBaseQuest();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FName QuestName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FGuid QuestGuid;
	
	UQSEObjectiveCollection* GetRootObjectiveCollection() const;
private:
	EQSEQuestState QuestState = EQSEQuestState::WaitingToStart;
protected:
	virtual UQSEObjectiveCollection* CreateRootObjectiveCollection();
	
	virtual void PopulateObjectives(UQSEObjectiveCollection* RootCollection);
	
	virtual void SetQuestState(EQSEQuestState State);
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void BeginPlay() override;
};
