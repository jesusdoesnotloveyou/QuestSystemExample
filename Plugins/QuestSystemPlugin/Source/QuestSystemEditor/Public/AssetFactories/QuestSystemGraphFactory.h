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

    // UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool CanCreateNew() const override;
    virtual bool ConfigureProperties() override;
    // End of UFactory interface

private:
    TSubclassOf<UQuestSystemGraph> ParentClass;
};
