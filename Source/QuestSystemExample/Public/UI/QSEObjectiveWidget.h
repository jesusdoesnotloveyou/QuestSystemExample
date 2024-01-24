// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QSEBaseObjective.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TreeView.h"
#include "QSEObjectiveWidget.generated.h"

class UTextBlock;
class UTreeView;

UCLASS()
class QUESTSYSTEMEXAMPLE_API UQSEObjectiveWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UQSEBaseObjective* Objective;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObjectiveNameText;

	UPROPERTY(meta = (BindWidget))
	UTreeView* SubObjectivesTreeView;

	UPROPERTY(meta = (BindWidget))
	UButton* ObjectiveButton;

	// It's okay
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override; 
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
private:
	UFUNCTION()
	void SetObjectiveExpansion();
};
