// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GraphEditorSettings.h"
#include "GraphEditorSettings_QuestSystemEditor.generated.h"

UENUM()
enum class EAutoLayoutStrategy : uint8
{
    Tree,
    ForceDirected,
};

UCLASS()
class QUESTSYSTEMEDITOR_API UGraphEditorSettings_QuestSystemEditor : public UGraphEditorSettings
{
	GENERATED_BODY()

public:
    UGraphEditorSettings_QuestSystemEditor();
    virtual ~UGraphEditorSettings_QuestSystemEditor() override;

    UPROPERTY(EditDefaultsOnly, Category = "AutoArrange")
    float OptimalDistance;
    
    /** TODO : AutoDisplay is need to be explained */
    /** TODO : Every property below is need to be explained */ // cause for now I do not have an idea why GraphEditor needs 'em
    
    UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
    EAutoLayoutStrategy AutoLayoutStrategy;

    UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
    int32 MaxIteration;

    UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
    bool bFirstPassOnly;

    UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
    bool bRandomInit;

    UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
    float InitTemperature;

    UPROPERTY(EditDefaultsOnly, AdvancedDisplay, Category = "AutoArrange")
    float CoolDownRate;
};
