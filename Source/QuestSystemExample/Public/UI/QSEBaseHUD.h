// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "QSEBaseHUD.generated.h"

class AQSEPlayerController;

UENUM(BlueprintType)
enum class EQSEWidgetType : uint8
{
	Inventory = 0,
	QuestJournal
};

UCLASS()
class QUESTSYSTEMEXAMPLE_API AQSEBaseHUD : public AHUD
{
	GENERATED_BODY()
public:
// 	UPROPERTY()
// 	TMap<EQSEWidgetType, UUserWidget*> GameWidgets;
	
	void CreateQuestJournalWidget(AQSEPlayerController* PlayerController);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> QuestJournalWidgetClass;

	virtual void BeginPlay() override;
};
