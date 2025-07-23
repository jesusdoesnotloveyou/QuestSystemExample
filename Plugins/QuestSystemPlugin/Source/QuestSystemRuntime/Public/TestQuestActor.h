// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestQuestActor.generated.h"

UCLASS()
class QUESTSYSTEMRUNTIME_API ATestQuestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestQuestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITORONLY_DATA
    
    UPROPERTY()
    UEdGraph* EdGraph;

#endif

    UPROPERTY()
    FName ActorTag;
};
