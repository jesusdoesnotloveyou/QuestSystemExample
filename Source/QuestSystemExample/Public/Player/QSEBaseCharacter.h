// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QSEBaseCharacter.generated.h"

class AQSEBaseQuest;
class UQuestSystemManagerComponent;

UCLASS()
class QUESTSYSTEMEXAMPLE_API AQSEBaseCharacter : public ACharacter
{
	GENERATED_BODY()
protected:

    UPROPERTY(VisibleAnywhere, Category = "Quests")
    UQuestSystemManagerComponent* ManagerComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AQSEBaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	TArray<AActor*> Quests;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UFUNCTION(/*BlueprintCallable*/)
	void Interact();
	
};
