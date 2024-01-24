// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseObjective.generated.h"

UCLASS()
class QUESTSYSTEMRUNTIME_API UBaseObjective : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category="Quest System")
	FName ObjectiveName;

	FText ObjectiveDescription;

	bool ObjectiveState = false;

protected:
	bool IsCompleted() const;
};
