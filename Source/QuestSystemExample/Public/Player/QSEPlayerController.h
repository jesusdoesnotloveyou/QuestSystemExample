// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QSEPlayerController.generated.h"

UCLASS()
class QUESTSYSTEMEXAMPLE_API AQSEPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	void OpenQuestJournal(); 
};
