// Quest System by JDNLY. All Rights Reserved

#include "AssetActions/QuestSystemGraphActions.h"
#include "QuestSystemGraph.h"
#include "AssetEditor/AssetEditor_QuestSystemEditor.h"

#define LOCTEXT_NAMESPACE "QuestSystemGraphActions"

FQuestSystemGraphActions::FQuestSystemGraphActions() {}

UClass* FQuestSystemGraphActions::GetSupportedClass() const
{
	return UQuestSystemGraph::StaticClass(); 
}

FText FQuestSystemGraphActions::GetName() const
{
	return LOCTEXT("QuestSystemGraphActionsName", "Quest Editor");
}

FColor FQuestSystemGraphActions::GetTypeColor() const
{
	return FColor::Yellow;
}

uint32 FQuestSystemGraphActions::GetCategories()
{
    return FModuleManager::Get().IsModuleLoaded("AssetTools") ? FAssetToolsModule::GetModule().Get().FindAdvancedAssetCategory(FName("Quest System Editor")) : EAssetTypeCategories::Gameplay;
}

void FQuestSystemGraphActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UQuestSystemGraph* Graph = Cast<UQuestSystemGraph>(*ObjIt))
		{
			TSharedRef<FAssetEditor_QuestSystemEditor> NewGraphEditor(new FAssetEditor_QuestSystemEditor());
			NewGraphEditor->InitQuestSystemEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
	//FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

#undef LOCTEXT_NAMESPACE