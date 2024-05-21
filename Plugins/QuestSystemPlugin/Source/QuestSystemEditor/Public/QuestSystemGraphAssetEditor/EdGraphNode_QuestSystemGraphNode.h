// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphNode_QuestSystemGraphNode.generated.h"

class UQuestSystemGraphNode;
class UEdGraph_QuestSystemGraph;
class SGraphNode_QuestSystemGraphNode;
//class UEdNode_QuestSystemGraphEdge;

UCLASS()
class QUESTSYSTEMEDITOR_API UEdGraphNode_QuestSystemGraphNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UEdGraphNode_QuestSystemGraphNode();
	virtual ~UEdGraphNode_QuestSystemGraphNode() override;

	void SetQuestSystemGraphNode(UQuestSystemGraphNode* InNode);
	
	UEdGraph_QuestSystemGraph* GetEdGraph() const;
    
	//~ Begin UEdGraphNode Interfaces
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//~ Gets the tooltip to display when over the node
	virtual FText GetTooltipText() const override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
    //~ End UEdGraphNode Interface

    // CanUserCopyNodes() and CanUserPasteNodes() may not be necessary, cause AssetEditor uses CanUserDeleteNode() and CanDuplicateNode() to check if it can copy or paste nodes
    virtual bool CanUserCopyNodes() const;
    virtual bool CanUserDeleteNode() const override;
	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserPasteNodes() const;

    // Should be connected somehow with the OnRenameNode() in FAssetEditor_QuestSystemEditor
    virtual void OnRenameNode(const FString& NewName) override {}
    
    virtual void NodeConnectionListChanged() override;
    
	// virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

#if WITH_EDITOR
	virtual void PostEditUndo() override;
    // Method to execute when node's properties are changed
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif
    /** check if the node can accept breakpoints */
    /** that function in UK2Node class */
    virtual bool CanPlaceBreakpoints() const { return false; }

public: 
    UPROPERTY(VisibleAnywhere, Instanced, Category = "QuestSystemGraphNode")
    UQuestSystemGraphNode* QuestSystemGraphNode;

    // Need a slate class for node
    SGraphNode_QuestSystemGraphNode* SEdNode;

private:
    bool bAllowCopy;
    bool bAllowDelete;
    bool bAllowDuplicate;
    bool bAllowPaste;
};
