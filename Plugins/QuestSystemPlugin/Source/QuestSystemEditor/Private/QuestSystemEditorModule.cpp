// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSystemEditorModule.h"
#include "QuestSystemGraphNodeFactory.h"

#define LOCTEXT_NAMESPACE "FQuestSystemEditorModule"

void FQuestSystemEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    // Register
    IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    const EAssetTypeCategories::Type AssetCategoryBit = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("UserDefinedAsset")),
        LOCTEXT("UserDefinedAssetCategory", "User Defined Asset"));
    AssetTypeAction = MakeShareable(new FQuestSystemGraphActions(AssetCategoryBit));
    AssetToolsModule.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());
    
    //QuestSystemGraphActions = MakeShared<FQuestSystemGraphActions>();
	//FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(QuestSystemGraphActions.ToSharedRef());
    
    // Register the factory for creating nodes
	QuestSystemGraphNodeFactory = MakeShareable(new FQuestSystemGraphNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(QuestSystemGraphNodeFactory);

    // Register the factory for creating pins
	//QuestSystemGraphNodePinFactory = MakeShareable(new FQuestSystemGraphNodePinFactory());
	//FEdGraphUtilities::RegisterVisualPinFactory(QuestSystemGraphNodePinFactory);
}

void FQuestSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// we call this function before unloading the module.

    if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AssetTypeAction.ToSharedRef());

    // Unregister the nodes factory
	FEdGraphUtilities::UnregisterVisualNodeFactory(QuestSystemGraphNodeFactory);
    // Unregister the pins factory
	//FEdGraphUtilities::RegisterVisualPinFactory(QuestSystemGraphNodePinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemEditorModule, QuestSystemPlugin)