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
	/**
     * Singleton-like access to this module's interface.  This is just for convenience!
     * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
     *
     * @return Returns singleton instance, loading the module on demand if needed
     */
    static inline FQuestSystemEditorModule& Get()
    {
    	return FModuleManager::LoadModuleChecked<FQuestSystemEditorModule>("QuestSystemEditor");
    }
    
    /**
     * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
     *
     * @return True if the module is loaded and ready to use
     */
    static inline bool IsAvailable()
    {
    	return FModuleManager::Get().IsModuleLoaded("QuestSystemEditor");
    }

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