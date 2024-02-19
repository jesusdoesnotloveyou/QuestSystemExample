// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class QUESTSYSTEMEDITOR_API FQuestSystemGraphActions : public FAssetTypeActions_Base
{
public:
	FQuestSystemGraphActions(EAssetTypeCategories::Type InAssetCategory);
private:
	EAssetTypeCategories::Type AssetTypeCategory;
public:
    // IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
    // End of IAssetTypeActions interface
};
