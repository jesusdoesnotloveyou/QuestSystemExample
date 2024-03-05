// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Nodes/QuestSystemGraphNode_Base.h"
#include "QuestSystemGraphNode_Branch.generated.h"

UCLASS()
class QUESTSYSTEMRUNTIME_API UQuestSystemGraphNode_Branch : public UQuestSystemGraphNode_Base
{
	GENERATED_BODY()
public:

    UQuestSystemGraphNode_Branch();
    virtual ~UQuestSystemGraphNode_Branch() override;

#if WITH_EDITOR
    virtual FText GetDescription_Implementation() const override;
    virtual FText GetNodeCategory_Implementation() const override;
    virtual FText GetNodeTitle_Implementation() const override;
#endif
};
