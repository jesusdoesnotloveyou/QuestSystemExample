// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdNode_QuestSystemGraphEdge.h"
#include "SGraphNode.h"

class UEdNode_QuestSystemGraphEdge;

class QUESTSYSTEMEDITOR_API SGraphNode_QuestSystemGraphEdge : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_QuestSystemGraphEdge){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdNode_QuestSystemGraphEdge* InNode);
};
