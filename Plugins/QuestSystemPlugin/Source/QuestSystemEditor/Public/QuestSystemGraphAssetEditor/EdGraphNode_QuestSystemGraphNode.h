// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphNode_QuestSystemGraphNode.generated.h"

class UQuestSystemGraphNode;
class UEdGraph_QuestSystemGraph;
class UAssetQuestSystemGraphSchema;
//class UEdNode_QuestSystemGraphEdge;

UCLASS()
class QUESTSYSTEMEDITOR_API UEdGraphNode_QuestSystemGraphNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UEdGraphNode_QuestSystemGraphNode();
	virtual ~UEdGraphNode_QuestSystemGraphNode() override;

	UPROPERTY()
	UQuestSystemGraphNode* QuestSystemGraphNode;

	void SetQuestSystemGraphNode(UQuestSystemGraphNode* InNode);
	UEdGraph_QuestSystemGraph* GetEdGraph() const;
	
	// Need a slate class for node
	// SEdNode_QuestSystemGraphNode* SEdNode;
	
	//~ Begin UEdGraphNode Interfaces
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//~ Gets the tooltip to display when over the node
	virtual FText GetTooltipText() const override;
    //~ End UEdGraphNode Interface
    
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

    virtual void NodeConnectionListChanged() override;
    
	// virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

	virtual void PostEditUndo() override;

    /** check if node can accept breakpoints */
    /** that function in UK2Node class */
    virtual bool CanPlaceBreakpoints() const { return false; }
};
