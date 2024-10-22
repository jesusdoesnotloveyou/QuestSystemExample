﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSystemEditorModule.h"
#include "AssetActions/QuestSystemGraphActions.h"
#include "QuestSystemGraphNodeFactory.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestSystemEditorModule, All, All);

#define LOCTEXT_NAMESPACE "FQuestSystemEditorModule"

// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
void FQuestSystemEditorModule::StartupModule()
{
    UE_LOG(LogQuestSystemEditorModule, Display, TEXT("QuestSystemEditorModule has been loaded"));
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    
    // Register new Category
    FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory(FName("Quest System Editor"), FText::FromString("Quest Editor"));
    
    // Create and register custom Asset actions
    RegisterAssetTypeAction(AssetTools, MakeShareable(new FQuestSystemGraphActions()));
    
    // Register the factory for creating nodes
	QuestSystemEditorNodeFactory = MakeShareable(new FQuestSystemGraphNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(QuestSystemEditorNodeFactory);

    // Register the factory for creating pins
	QuestSystemEditorNodePinFactory = MakeShareable(new FQuestSystemGraphNodePinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(QuestSystemEditorNodePinFactory);

    // Register the factory for creating connections
    QuestSystemEditorPinConnectionFactory = MakeShareable(new FQuestSystemGraphPinConnectionFactory());
    FEdGraphUtilities::RegisterVisualPinConnectionFactory(QuestSystemEditorPinConnectionFactory);
}

// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
// we call this function before unloading the module.
void FQuestSystemEditorModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
    {
        IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

        for (auto& AssetTypeAction : CreatedQuestSystemEditorAssetTypeActions)
        {
            AssetTools.UnregisterAssetTypeActions(AssetTypeAction.ToSharedRef());
        }
    }
    
    // Unregister the nodes factory
    if (QuestSystemEditorNodeFactory.IsValid())
    {
        FEdGraphUtilities::UnregisterVisualNodeFactory(QuestSystemEditorNodeFactory);
        QuestSystemEditorNodeFactory.Reset();
    }
    
    // Unregister the pins factory
    if (QuestSystemEditorNodePinFactory.IsValid())
    {
        FEdGraphUtilities::UnregisterVisualPinFactory(QuestSystemEditorNodePinFactory);
        QuestSystemEditorNodePinFactory.Reset();
    }
    // Unregister the connections factory
    if (QuestSystemEditorPinConnectionFactory.IsValid())
    {
        FEdGraphUtilities::UnregisterVisualPinConnectionFactory(QuestSystemEditorPinConnectionFactory);
        QuestSystemEditorPinConnectionFactory.Reset();
    }
}

void FQuestSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, /*Custom asset type */ TSharedRef<IAssetTypeActions> Action)
{
    // Register new Asset type
    AssetTools.RegisterAssetTypeActions(Action);
    CreatedQuestSystemEditorAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemEditorModule, QuestSystemEditor)