// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdNodeEdge_QuestSystemGraphEdge.h"
#include "SGraphNode.h"

class UEdNodeEdge_QuestSystemGraphEdge;

class QUESTSYSTEMEDITOR_API SNodeEdge_QuestSystemGraphEdge : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SNodeEdge_QuestSystemGraphEdge){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdNodeEdge_QuestSystemGraphEdge* InNode);
};
