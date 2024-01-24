// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystemGraphNode.h"
#include "QuestSystemGraphEdge.generated.h"

UCLASS()
class QUESTSYSTEMRUNTIME_API UQuestSystemGraphEdge : public UObject
{
	GENERATED_BODY()
public:
	UQuestSystemGraphEdge();
	virtual ~UQuestSystemGraphEdge() override;

	UPROPERTY(VisibleAnywhere, Category = "QuestSystemGraphEdge")
	UQuestSystemGraph* Graph;
	
	UPROPERTY(VisibleAnywhere, Category = "QuestSystemGraphEdge")
	UQuestSystemGraphEdge* StartNode;
	
	UPROPERTY(VisibleAnywhere, Category = "QuestSystemGraphEdge")
	UQuestSystemGraphEdge* EndNode;

	UFUNCTION(Category = "QuestSystemGraphEdge")
	UQuestSystemGraph* GetGraph() const;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphEdgeEditor")
	bool bShouldDrawTitle = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphEdgeEditor")
	FText NodeTitle;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphEdgeEditor")
	FLinearColor EdgeColor = FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
#endif

#if WITH_EDITOR
	virtual FText GetNodeTitle() const { return NodeTitle; }
	FLinearColor GetEdgeColor() const { return EdgeColor; }

	virtual void SetNodeTitle(const FText& NewTitle);
#endif
};
