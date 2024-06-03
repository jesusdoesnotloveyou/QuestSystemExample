// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;
class IAssetTools;
class FQuestSystemGraphActions;
struct FQuestSystemGraphNodeFactory;
struct FQuestSystemGraphNodePinFactory;
struct FQuestSystemGraphPinConnectionFactory;

class FQuestSystemEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
    /* Called when the module is loaded */
	virtual void StartupModule() override;
    /* Called when the module is unloaded */
	virtual void ShutdownModule() override;

private:
    void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
    
private:
 	TArray<TSharedPtr<IAssetTypeActions>> CreatedQuestSystemEditorAssetTypeActions;
 	
	TSharedPtr<FQuestSystemGraphNodeFactory> QuestSystemEditorNodeFactory;
	TSharedPtr<FQuestSystemGraphNodePinFactory> QuestSystemEditorNodePinFactory;
	TSharedPtr<FQuestSystemGraphPinConnectionFactory> QuestSystemEditorPinConnectionFactory;
};