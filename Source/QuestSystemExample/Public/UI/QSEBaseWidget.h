// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QSEBaseWidget.generated.h"

class UTreeView;
class AQSEBaseCharacter;

UCLASS() 
class QUESTSYSTEMEXAMPLE_API UQSEBaseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTreeView* QuestTreeView;

	virtual FReply NativeOnPreviewKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
private:
	void Close();
	
	void FillQuestTreeView(AQSEBaseCharacter* PlayerCharacter) const;
};
