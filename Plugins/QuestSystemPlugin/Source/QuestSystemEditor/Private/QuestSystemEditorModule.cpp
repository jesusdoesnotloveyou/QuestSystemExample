// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSystemEditorModule.h"
#include "QuestSystemGraphNodeFactory.h"

#define LOCTEXT_NAMESPACE "FQuestSystemEditorModule"

void FQuestSystemEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

    // Register new Category
    const EAssetTypeCategories::Type QuestSystemEditorAssetCategoryBit = AssetToolsModule.RegisterAdvancedAssetCategory(FName("Quest System Editor"),
        LOCTEXT("FQuestSystemEditorModule", "Quest System Editor"));

    QuestSystemEditorAssetAction = MakeShareable(new FQuestSystemGraphActions(QuestSystemEditorAssetCategoryBit));
    AssetToolsModule.RegisterAssetTypeActions(QuestSystemEditorAssetAction.ToSharedRef());
    
    // Register the factory for creating nodes
	QuestSystemEditorNodeFactory = MakeShareable(new FQuestSystemGraphNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(QuestSystemEditorNodeFactory);

    // Register the factory for creating pins
	//QuestSystemGraphNodePinFactory = MakeShareable(new FQuestSystemGraphNodePinFactory());
	//FEdGraphUtilities::RegisterVisualPinFactory(QuestSystemGraphNodePinFactory);
}

void FQuestSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// we call this function before unloading the module.

    if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(QuestSystemEditorAssetAction.ToSharedRef());

    // Unregister the nodes factory
	FEdGraphUtilities::UnregisterVisualNodeFactory(QuestSystemEditorNodeFactory);
    // Unregister the pins factory
	//FEdGraphUtilities::RegisterVisualPinFactory(QuestSystemGraphNodePinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemEditorModule, QuestSystemEditor)