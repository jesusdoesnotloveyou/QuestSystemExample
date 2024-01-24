// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QSECoreTypes.h"
#include "QSEBaseObjective.generated.h"

class AQSEBaseQuest;

UCLASS(Blueprintable)
class QUESTSYSTEMEXAMPLE_API UQSEBaseObjective : public UObject
{
	GENERATED_BODY()
public:
	FOnCompletedObjectiveSignature OnCompletedObjective;
	FOnActivateObjectiveSignature OnActivateObjective;
	
	//const FText& GetObjectiveName() const { return ObjectiveName; }

    UFUNCTION()
    void OnCompletedObjective_1(UQSEBaseObjective* Objective);
    
	UFUNCTION(BlueprintCallable)
	bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable)
	virtual bool IsComplete() const { return bIsComplete; }

	//FUNCTION(BlueprintNativeEvent)
	virtual void ActivateObjective();
	//virtual void ActivateObjective_Implementation();
	
private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	//FText ObjectiveName;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	bool bIsComplete = false;

protected:
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	bool bIsActive = false;
};
