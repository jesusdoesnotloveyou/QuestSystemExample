// Quest System by JDNLY. All Rights Reserved


#include "TestQuestActor.h"

ATestQuestActor::ATestQuestActor()
{
	PrimaryActorTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
    EdGraph = nullptr;
#endif
}

void ATestQuestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestQuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

