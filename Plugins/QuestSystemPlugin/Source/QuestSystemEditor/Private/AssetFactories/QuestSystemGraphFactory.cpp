// Quest System by JDNLY. All Rights Reserved


#include "AssetFactories/QuestSystemGraphFactory.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"
#include "QuestSystemGraph.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"
#include "TestQuestActor.h"

#define LOCTEXT_NAMESPACE "QuestSystemGraphFactory"

class FAssetClassParentFilter : public IClassViewerFilter
{
public:
    FAssetClassParentFilter() : DisallowedClassFlags(CLASS_None), bDisallowBlueprintBase(false) {}

    /** All children of these classes will be included unless filtered out by another setting. */
	TSet<const UClass*> AllowedChildrenOfClasses;

	/** Disallowed class flags. */
	EClassFlags DisallowedClassFlags;

	/** Disallow blueprint base classes. */
	bool bDisallowBlueprintBase;

    virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
    {
        const bool bAllowed = !InClass->HasAnyClassFlags(DisallowedClassFlags)
            && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;

        if (bAllowed && bDisallowBlueprintBase)
        {
            if (FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass))
            {
                return false;
            }
        }

        return bAllowed;
    }

    virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
    {
        if (bDisallowBlueprintBase)
        {
            return false;
        }

        return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
            && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
    }
};

    
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
    if (ParentClass)
    {
        return NewObject<UQuestSystemGraph>(InParent, ParentClass, Name, Flags | RF_Transactional);
    }
    else
    {
        check(Class->IsChildOf(UQuestSystemGraph::StaticClass()));
        return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
    }
}

bool UQuestSystemGraphFactory::CanCreateNew() const
{
    return bCreateNew;
}

bool UQuestSystemGraphFactory::ConfigureProperties()
{
    // Set null pointer to the ParentClass to check for selection
    ParentClass = nullptr;

    // Load the classviewer module to display a class picker
    FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

    // Fill in options
    FClassViewerInitializationOptions Options;
    Options.Mode = EClassViewerMode::ClassPicker;

    TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
    Options.ClassFilter = Filter;
    
    Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
    	Filter->AllowedChildrenOfClasses.Add(UQuestSystemGraph::StaticClass());
    
    	const FText TitleText = LOCTEXT("CreateGenericGraphAssetOptions", "Pick Generic Graph Class");
    	UClass* ChosenClass = nullptr;
    	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UQuestSystemGraph::StaticClass());
    
    	if (bPressedOk)
    	{
    		ParentClass = ChosenClass;
    	}
    
    	return bPressedOk;
}

#undef LOCTEXT_NAMESPACE