// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "KismetNodes/SGraphNodeK2Base.h"

class UEdGraphNode_QuestSystemGraphNode;
class UK2Node_QuestSystemNode;

class QUESTSYSTEMEDITOR_API SGraphNode_QuestSystemGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_QuestSystemGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphNode_QuestSystemGraphNode* InNode);
};

class QUESTSYSTEMEDITOR_API SGraphNode_QuestSystemK2GraphNode : public SGraphNodeK2Base
{
public:
    SLATE_BEGIN_ARGS(SGraphNode_QuestSystemK2GraphNode) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, UK2Node_QuestSystemNode* InNode);
};