// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdNode_QuestSystemGraphEdge.generated.h"

class UQuestSystemGraphEdge;
class UEdGraphNode_QuestSystemGraphNode;

UCLASS()
class QUESTSYSTEMEDITOR_API UEdNode_QuestSystemGraphEdge : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdNode_QuestSystemGraphEdge();
	virtual ~UEdNode_QuestSystemGraphEdge() override;

	UPROPERTY()
	class UEdGraph* Graph;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "QuestSystemGraphEdge")
	UQuestSystemGraphEdge* QuestSystemGraphEdge;

	void SetEdge(UQuestSystemGraphEdge* InEdge);

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void CreateConnections(UEdGraphNode_QuestSystemGraphNode* Start, UEdGraphNode_QuestSystemGraphNode* End);

	UEdGraphNode_QuestSystemGraphNode* GetStartNode();
	UEdGraphNode_QuestSystemGraphNode* GetEndNode();
};
