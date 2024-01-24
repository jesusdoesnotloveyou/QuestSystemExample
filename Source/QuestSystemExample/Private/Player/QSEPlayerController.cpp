// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/QSEPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/QSEBaseHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEPlayerController, All, All);

void AQSEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("OpenQuestJournal", IE_Pressed, this, &AQSEPlayerController::OpenQuestJournal);
}

void AQSEPlayerController::OpenQuestJournal()
{
	const auto PlayerHUD = Cast<AQSEBaseHUD>(GetHUD());
	if (!PlayerHUD) return;

	PlayerHUD->CreateQuestJournalWidget(this);
	
	// PlayerHUD->GameWidgets[EQSEWidgetType::QuestJournal]->SetVisibility(ESlateVisibility::Visible);
	//
	// SetInputMode(FInputModeUIOnly());
	// bShowMouseCursor = true;
}