// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QSECoreTypes.h"
#include "QSEGameModeBase.generated.h"

UCLASS()
class QUESTSYSTEMEXAMPLE_API AQSEGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AQSEGameModeBase();
	
	FOnQuestStateChangedSignature OnQuestStateChanged;

private:
	void SetQuestState(EQSEQuestState State);
};
