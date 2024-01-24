// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/QSEBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "Player/QSEPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEBaseHUD, All, All);

void AQSEBaseHUD::CreateQuestJournalWidget(AQSEPlayerController* PlayerController)
{
	UE_LOG(LogQSEBaseHUD, Warning, TEXT("Quest journal is created and opened"));
	const auto PlayerWidget = CreateWidget<UUserWidget>(PlayerController, QuestJournalWidgetClass);
	if (!PlayerWidget) return;

	PlayerWidget->AddToViewport();
	PlayerWidget->SetFocus();
	PlayerWidget->SetVisibility(ESlateVisibility::Visible);
}

void AQSEBaseHUD::BeginPlay()
{
	Super::BeginPlay();
// 	GameWidgets.Add(EQSEWidgetType::QuestJournal, CreateWidget<UUserWidget>(GetWorld(), QuestJournalWidgetClass));
//
// 	for (const auto GameWidgetPair : GameWidgets)
// 	{/
// 		const auto GameWidget = GameWidgetPair.Value;
// 		if (!GameWidget) continue;
// 		
// 		GameWidget->AddToViewport();
// 		GameWidget->SetVisibility(ESlateVisibility::Hidden);
// 		UE_LOG(LogQSEBaseHUD, Warning, TEXT("Quest journal widget is hidden"));
// 	}
}
