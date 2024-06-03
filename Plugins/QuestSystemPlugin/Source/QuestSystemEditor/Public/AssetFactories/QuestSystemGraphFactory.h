// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "QuestSystemGraphFactory.generated.h"

class UQuestSystemGraph;

UCLASS()
class QUESTSYSTEMEDITOR_API UQuestSystemGraphFactory : public UFactory
{
	GENERATED_BODY()
public:
	UQuestSystemGraphFactory();

private:
    // UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool CanCreateNew() const override;
    // End of UFactory interface
};
