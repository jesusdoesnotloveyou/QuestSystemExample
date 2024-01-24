// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/QSEObjectiveWidget.h"

#include "QSEObjectiveCollection.h"
#include "QuestSystemEntities/QSEBaseObjective.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEObjectiveWidget, All, All);

void UQSEObjectiveWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ObjectiveButton)
	{
		ObjectiveButton->OnClicked.AddDynamic(this, &UQSEObjectiveWidget::SetObjectiveExpansion);
		UE_LOG(LogQSEObjectiveWidget, Warning, TEXT("Successfully bind SetObjectiveExpamsion() to ObjectiveButton"));
	}
}

void UQSEObjectiveWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	//IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	Objective = Cast<UQSEBaseObjective>(ListItemObject);
	if (!Objective) return;

	ObjectiveNameText->SetText(FText::FromString(Objective->GetName()));

	const auto ObjectiveCollection = Cast<UQSEObjectiveCollection>(Objective);
	if (!ObjectiveCollection) return;

	//Class* const& might be use in range-for
	for (const auto SubObjective : ObjectiveCollection->Objectives)
	{
		if (!SubObjective) continue;
		SubObjectivesTreeView->AddItem(SubObjective);
		UE_LOG(LogQSEObjectiveWidget, Warning, TEXT("ObjectCollection has a list of objectives"));
	}
}

void UQSEObjectiveWidget::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	//IUserListEntry::NativeOnItemExpansionChanged(bIsExpanded);
	SubObjectivesTreeView->SetVisibility(bIsExpanded ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void UQSEObjectiveWidget::SetObjectiveExpansion()
{
	const auto TreeView = Cast<UTreeView>(GetOwningListView());
	if (!TreeView || !Objective) return;

	TreeView->SetItemExpansion(Objective, !IsListItemExpanded());
}
