// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "QuestSystemGraphNode.h"
#include "QuestSystemGraphEdge.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystemGraph.generated.h"

UCLASS(BlueprintType)
class QUESTSYSTEMRUNTIME_API UQuestSystemGraph : public UObject
{
	GENERATED_BODY()
public:
	UQuestSystemGraph();
	virtual ~UQuestSystemGraph() override;

	UPROPERTY(EditDefaultsOnly, Category= "QuestSystemGraph")
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph")
	TSubclassOf<UQuestSystemGraphNode> NodeType;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph")
	TSubclassOf<UQuestSystemGraphEdge> EdgeType; 

	UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraph")
	TArray<UQuestSystemGraphNode*> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraph")
	TArray<UQuestSystemGraphNode*> AllNodes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSystemGraph")
	bool bEdgeEnabled;

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
	void Print(bool ToConsole = true, bool ToScreen = true);

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
	int GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
	void GetNodesByLevel(int Level, TArray<UQuestSystemGraphNode*>& Nodes);

	void ClearGraph();

	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UEdGraph* EdGraph;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph_Editor")
	bool bCanRenameNode; 

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph_Editor")
	bool bCanBeCyclical;
	
#endif
};
