// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystemEntities/QSEBaseObjective.h"
#include "QSEObjectiveCollection.generated.h"

UCLASS()
class QUESTSYSTEMEXAMPLE_API UQSEObjectiveCollection : public UQSEBaseObjective
{
	GENERATED_BODY()
public:
    UQSEObjectiveCollection();
    
	UPROPERTY(/*EditDefaultsOnly, BlueprintReadWrite, Category = "Objectives"*/)
	TArray<UQSEBaseObjective*> Objectives;

	void AddObjective(UQSEBaseObjective* NewObjective);
    
	virtual bool IsComplete() const override;

	virtual void ActivateObjective/*_Implementation*/() override;

    UFUNCTION()
	void OnActivateObjective();

    UFUNCTION()
    void ContinueActivatingObjectives();
private:
	bool bIsOrderRequired;

	UQSEBaseObjective* FindNextIncompleteObjective();
    // UFUNCTION()
	// void OnCompletedObjective(UQSEBaseObjective* Objective);
};
