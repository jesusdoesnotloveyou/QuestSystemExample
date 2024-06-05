// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Nodes/QuestSystemGraphNode.h"
#include "QuestSystemGraph.generated.h"

class UQuestSystemContext;
class UQuestSystemGraphEdge;

/**
 *  Can be the object which contains all the logic for quest
 */
UCLASS(BlueprintType)
class QUESTSYSTEMRUNTIME_API UQuestSystemGraph : public UObject
{
	GENERATED_BODY()
public:
	UQuestSystemGraph();
	virtual ~UQuestSystemGraph() override;

#pragma region Variables

protected:
    UPROPERTY()
    FGuid GraphGUID;

public:
	UPROPERTY(EditDefaultsOnly, Category= "QuestSystemGraph")
	FString Name;

    UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraph")
    UQuestSystemGraphNode* StartNode = nullptr;
    
	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph")
	TSubclassOf<UQuestSystemGraphNode> NodeType;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph")
	TSubclassOf<UQuestSystemGraphEdge> EdgeType;

	UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraph")
	TArray<UQuestSystemGraphNode*> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category = "QuestSystemGraph")
	TArray<UQuestSystemGraphNode*> AllNodes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSystemGraph")
	bool bEdgeEnabled;
    
    UPROPERTY(Transient)
    UQuestSystemContext* Context = nullptr;

#pragma endregion

#pragma region Functions

public:
    UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
    UQuestSystemGraphNode* GetStartNode() const;
    
    UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
    TArray<UQuestSystemGraphNode*> GetRootNodes() const;
    
    UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
    TArray<UQuestSystemGraphNode*> GetAllNodes() const;
    
	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
	void Print(bool ToConsole = true, bool ToScreen = true);

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
	int GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category = "QuestSystemGraph")
	void GetNodesByLevel(int Level, TArray<UQuestSystemGraphNode*>& Nodes);

    void CreateGraph();
	void ClearGraph();

#pragma endregion 
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UEdGraph* EdGraph;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph_Editor")
	bool bCanRenameNode; 

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystemGraph_Editor")
	bool bCanBeCyclical;
	
#endif

#if WITH_EDITOR

public:

    template<class T>
    T* ConstructQuestSystemNode(TSubclassOf<UQuestSystemGraphNode> QuestNodeClass = T::StaticClass())
    {
        T* QuestSystemNode = NewObject<T>(this, QuestNodeClass, NAME_None, RF_Transactional);
        QuestSystemNode->OnCreatedInEditor();
        return QuestSystemNode;
    }

#endif
};
