// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_QuestSystemGraph.generated.h"

class UQuestSystemGraph; 
class UQuestSystemGraphNode; 
class UQuestSystemGraphEdge;
class UEdGraphNode_QuestSystemGraphNode;
class UEdNode_QuestSystemGraphEdge;

UCLASS()
class QUESTSYSTEMEDITOR_API UEdGraph_QuestSystemGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	UEdGraph_QuestSystemGraph();
	virtual ~UEdGraph_QuestSystemGraph() override;

	UQuestSystemGraph* GetGenericGraph() const;

	virtual void RebuildGraph();

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;
	virtual void PostEditUndo() override;

	UPROPERTY(Transient)
	TMap<UQuestSystemGraphNode*, UEdGraphNode_QuestSystemGraphNode*> NodeMap;
    UPROPERTY(Transient)
    TMap<UQuestSystemGraphEdge*, UEdNode_QuestSystemGraphEdge*> EdgeMap;

protected:
	void Clear();

	void SortNodes(UQuestSystemGraphNode* RootNode);
};
