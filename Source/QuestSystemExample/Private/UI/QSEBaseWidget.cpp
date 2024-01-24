// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/QSEBaseWidget.h"
#include "Input/Reply.h"
#include "Player/QSEBaseCharacter.h"
#include "Player/QSEPlayerController.h"

#include "QSEBaseQuest.h"
#include "QSEObjectiveCollection.h"
#include "Components/TreeView.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEBaseWidget, All, All);

void UQSEBaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const auto PlayerController = Cast<AQSEPlayerController>(GetOwningPlayer());
	if (!PlayerController) return;

	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->SetShowMouseCursor(true);

	const auto PlayerCharacter = Cast<AQSEBaseCharacter>(GetOwningPlayerPawn());
	if (!PlayerCharacter) return;

	PlayerCharacter->DisableInput(PlayerController);
	UE_LOG(LogQSEBaseWidget, Warning, TEXT("Quest journal is showing up"));
	FillQuestTreeView(PlayerCharacter);
	UE_LOG(LogQSEBaseWidget, Warning, TEXT("QuestTreeView is filled"));
}

FReply UQSEBaseWidget::NativeOnPreviewKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::J)
	{
		UE_LOG(LogQSEBaseWidget, Warning, TEXT("Quest journal is closed"));
		Close();
		Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply UQSEBaseWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return FReply::Handled();
}

void UQSEBaseWidget::Close()
{
	const auto PlayerController = Cast<AQSEPlayerController>(GetOwningPlayer());
	if (!PlayerController) return;

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);

	const auto PlayerCharacter = Cast<AQSEBaseCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;
	PlayerCharacter->EnableInput(PlayerController);

	RemoveFromParent();
}

void UQSEBaseWidget::FillQuestTreeView(AQSEBaseCharacter* PlayerCharacter) const
{
	for (const auto QuestActor : PlayerCharacter->Quests)
	{
		const auto Quest = Cast<AQSEBaseQuest>(QuestActor);
		if (!Quest) continue;
	    
		QuestTreeView->AddItem(Quest->GetRootObjectiveCollection());
		UE_LOG(LogQSEBaseWidget, Warning, TEXT("Quest item added"));
	}
}