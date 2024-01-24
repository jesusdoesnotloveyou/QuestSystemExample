#pragma once
#include "QSECoreTypes.generated.h"

UENUM(BlueprintType)
enum class EQSEQuestState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Completed,
	Failed
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStateChangedSignature, EQSEQuestState);

class UQSEBaseObjective;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompletedObjectiveSignature, class UQSEBaseObjective*, Objective);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivateObjectiveSignature);