// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
// #include "Misc/Guid.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BaseQuest.generated.h"

class UBaseObjective;
class USphereComponent;
class UBillboardComponent;

UCLASS(Abstract)
class QUESTSYSTEMRUNTIME_API ABaseQuest : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest Object Settings")
	UBillboardComponent* QuestSpriteIcon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest Object Settings")
	USphereComponent* LogicCollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Quest System")
	FName QuestName;
	
	UPROPERTY(VisibleAnywhere, Category="Quest System")
	TArray<TSubclassOf<UBaseObjective>> Objectives;

	UPROPERTY(VisibleDefaultsOnly, Category="Quest System")
	FGuid QuestGuid;

	//FOnQuestStateChangedSignature OnQuestStateChanged;
	
	TArray<TSubclassOf<UBaseObjective>>& GetObjectives();
	
	ABaseQuest();
private:
	//EQuestState QuestState = EQuestState::WaitingToStart;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//virtual EQuestState GetQuestState() const;
};
