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

UCLASS()
class QUESTSYSTEMRUNTIME_API UQuestSystemGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UQuestSystemGraphNode();
	virtual ~UQuestSystemGraphNode() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestSystemGraphNode")
	UQuestSystemGraph* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraphNode")
	TArray<UQuestSystemGraphNode*> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraphNode")
	TArray<UQuestSystemGraphNode*> ChildrenNodes;

	TMap<UQuestSystemGraphNode*, UQuestSystemGraphEdge*> Edges;

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraphNode")
	virtual UQuestSystemGraphEdge* GetEdge(UQuestSystemGraphNode* ChildNode);

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraphNode")
	UQuestSystemGraph* GetGraph() const;

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraphNode")
	bool IsLeafNode() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "QuestSystemGraphNode")
	FText GetDescription() const;
	virtual FText GetDescription_Implementation() const;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	TSubclassOf<UQuestSystemGraph> CompatibleGraphType;
	
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraphNodeEditor")
	FText NodeTitle;

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
	virtual bool IsNameEditable() const;

	virtual FLinearColor GetBackgroundColor() const;

	virtual FText GetNodeTitle() const;

	virtual void SetNodeTitle(const FText& NewTitle);

	virtual bool CanCreateConnection(UQuestSystemGraphNode* Other, FText& ErrorMessage);

	virtual bool CanCreateConnectionTo(UQuestSystemGraphNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage);
	virtual bool CanCreateConnectionFrom(UQuestSystemGraphNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage);

#endif
};
