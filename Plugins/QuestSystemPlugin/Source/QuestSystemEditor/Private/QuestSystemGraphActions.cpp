// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphActions.h"
#include "QuestSystemGraph.h"
#include "QuestSystemGraphAssetEditor/AssetEditor_QuestSystemEditor.h"

#define LOCTEXT_NAMESPACE "QuestSystemGraphActions"

FQuestSystemGraphActions::FQuestSystemGraphActions(EAssetTypeCategories::Type InAssetCategory)
    : AssetTypeCategory(InAssetCategory) {}

UClass* FQuestSystemGraphActions::GetSupportedClass() const
{
	return UQuestSystemGraph::StaticClass(); 
}

FText FQuestSystemGraphActions::GetName() const
{
	return LOCTEXT("QuestSystemGraphActions", "Quest Editor");
}

FColor FQuestSystemGraphActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FQuestSystemGraphActions::GetCategories()
{
	return AssetTypeCategory;
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