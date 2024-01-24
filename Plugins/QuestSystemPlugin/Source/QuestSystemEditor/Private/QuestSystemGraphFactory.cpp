// Quest System by JDNLY. All Rights Reserved


#include "QuestSystemGraphFactory.h"

UQuestSystemGraphFactory::UQuestSystemGraphFactory()
{
	// To create asset in the Content Browser
    bCreateNew = true;
    // To avoid opening the editor after creating the asset
	bEditAfterNew = false;
	// The class associated with the asset
	SupportedClass = UQuestSystemGraph::StaticClass();
}

UObject* UQuestSystemGraphFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    check(Class->IsChildOf(SupportedClass));
	return NewObject<UQuestSystemGraph>(InParent, Class, Name, Flags);
}

bool UQuestSystemGraphFactory::CanCreateNew() const
{
    return bCreateNew;
}
