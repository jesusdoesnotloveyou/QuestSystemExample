// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystemGraphNode.generated.h"

class UQuestSystemGraph;
class UQuestSystemGraphEdge;

UENUM(BlueprintType)
enum class ENodeLimit : uint8
{
	Unlimited,
	Limited
};

UCLASS(/*Abstract,*/ BlueprintType)
class QUESTSYSTEMRUNTIME_API UQuestSystemGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UQuestSystemGraphNode();
	virtual ~UQuestSystemGraphNode() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestSystemGraphNode")
	UQuestSystemGraph* Graph;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestSystemGraphNode")
	TArray<UQuestSystemGraphNode*> ParentNodes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestSystemGraphNode")
	TArray<UQuestSystemGraphNode*> ChildrenNodes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestSystemGraphNode")
	TMap<UQuestSystemGraphNode*, UQuestSystemGraphEdge*> Edges;

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraphNode")
	virtual UQuestSystemGraphEdge* GetEdge(UQuestSystemGraphNode* ChildNode);

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraphNode")
	UQuestSystemGraph* GetGraph() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestSystemGraphNode")
    FGuid NodeGUID;

private:
    UPROPERTY(VisibleAnywhere, Category = "QuestSystemGraphNode")
    UWorld* OwningWorld;
    
public:
	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraphNode")
	bool IsLeafNode() const;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	TSubclassOf<UQuestSystemGraph> CompatibleGraphType;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	FText NodeTitle;

    UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
    FText NodeTooltipText;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	FText ContextMenuName;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	FLinearColor BackgroundColor;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor") 
	ENodeLimit ParentLimitType;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor", meta = (ClampMin = "0", EditCondition = "ParentLimitType == ENodeLimit::Limited")) 
	int32 ParentLimit;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	ENodeLimit ChildrenLimitType;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor", meta = (ClampMin = "0", EditCondition = "ChildrenLimitType == ENodeLimit::Limited")) 
	int32 ChildrenLimit;
#endif

#if WITH_EDITOR
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "QuestSystemGraphNode")
    FText GetDescription() const;
    virtual FText GetDescription_Implementation() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="QuestSystemGraphNode")
    FText GetNodeCategory() const;
    virtual FText GetNodeCategory_Implementation() const;
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="QuestSystemGraphNode")
    FText GetNodeTooltipText() const;
    virtual FText GetNodeTooltipText_Implementation() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="QuestSystemGraphNode")
	FText GetNodeTitle() const;
	virtual FText GetNodeTitle_Implementation() const;

	virtual bool IsNameEditable() const;

    virtual FLinearColor GetBackgroundColor() const;

	virtual void SetNodeTitle(const FText& NewTitle);

	virtual bool CanCreateConnection(UQuestSystemGraphNode* Other, FText& ErrorMessage);

	virtual bool CanCreateConnectionTo(UQuestSystemGraphNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage);
	virtual bool CanCreateConnectionFrom(UQuestSystemGraphNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage);

#endif
};
