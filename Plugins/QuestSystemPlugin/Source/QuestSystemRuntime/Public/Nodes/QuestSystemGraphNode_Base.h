// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "QuestSystemGraphNode.h"
#include "QuestSystemGraphNode_Base.generated.h"

UCLASS()
class QUESTSYSTEMRUNTIME_API UQuestSystemGraphNode_Base : public UQuestSystemGraphNode
{
	GENERATED_BODY()
public:

    UQuestSystemGraphNode_Base();
    virtual ~UQuestSystemGraphNode_Base() override;

#if WITH_EDITOR
    virtual FText GetDescription_Implementation() const override;
    virtual FText GetNodeCategory_Implementation() const override;
    virtual FText GetNodeTitle_Implementation() const override;
#endif
};
