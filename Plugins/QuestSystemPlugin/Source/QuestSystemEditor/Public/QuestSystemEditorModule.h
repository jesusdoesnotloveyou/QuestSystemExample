// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "QuestSystemGraphActions.h"

class FQuestSystemGraphNodeFactory;
class FQuestSystemGraphNodePinFactory;

class FQuestSystemEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<class FQuestSystemGraphActions> AssetTypeAction;
	
	TSharedPtr<class FQuestSystemGraphNodeFactory> QuestSystemGraphNodeFactory;
	TSharedPtr<class FQuestSystemGraphNodePinFactory> QuestSystemGraphNodePinFactory;
};