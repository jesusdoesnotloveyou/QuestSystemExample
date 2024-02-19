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
    
    /* Called when the module is loaded */
	virtual void StartupModule() override;

    /* Called when the module is unloaded */
	virtual void ShutdownModule() override;

private:
 	TSharedPtr<class FQuestSystemGraphActions> QuestSystemEditorAssetAction;
    
	TSharedPtr<class FQuestSystemGraphNodeFactory> QuestSystemEditorNodeFactory;
	TSharedPtr<class FQuestSystemGraphNodePinFactory> QuestSystemEditorNodePinFactory;
};