// Fill out your copyright notice in the Description page of Project Settings.


#include "QSEGameModeBase.h"
#include "Player/QSEBaseCharacter.h"
#include "Player/QSEPlayerController.h"
#include "UI/QSEBaseHUD.h"

AQSEGameModeBase::AQSEGameModeBase()
{
	DefaultPawnClass = AQSEBaseCharacter::StaticClass();
	PlayerControllerClass = AQSEPlayerController::StaticClass();
	HUDClass = AQSEBaseHUD::StaticClass();
}

void AQSEGameModeBase::SetQuestState(EQSEQuestState State)
{
	
}