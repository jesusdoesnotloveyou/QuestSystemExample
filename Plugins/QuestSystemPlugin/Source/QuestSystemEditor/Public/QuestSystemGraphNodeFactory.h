// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"
#include "EdGraph/EdGraphNode.h"

class QUESTSYSTEMEDITOR_API FQuestSystemGraphNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};

class QUESTSYSTEMEDITOR_API FQuestSystemGraphNodePinFactory : public FGraphPanelPinFactory
{
public:
	//virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;
};