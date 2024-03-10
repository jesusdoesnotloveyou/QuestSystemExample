// Quest System by JDNLY. All Rights Reserved


#include "Nodes/QuestSystemGraphNode_Branch.h"

#define LOCTEXT_NAMESPACE "QuestSystemGraphNode_Branch"

UQuestSystemGraphNode_Branch::UQuestSystemGraphNode_Branch()
{
#if WITH_EDITORONLY_DATA
    NodeTitle = LOCTEXT("QuestSystemGraphNode_BranchNodeTitle", "Branch Node");
    NodeTooltipText = LOCTEXT("QuestSystemGraphNode_BranchTooltip", "The node contains some condition for the next step of a Quest");;
    ContextMenuName = LOCTEXT("QuestSystemGraphNode_BranchContextMenuName", "Branch Node");
    BackgroundColor = FLinearColor::Blue;
#endif
}

UQuestSystemGraphNode_Branch::~UQuestSystemGraphNode_Branch()
{
    
}

FText UQuestSystemGraphNode_Branch::GetDescription_Implementation() const
{
    return LOCTEXT("QuestSystemGraphNode_BranchDescription", "Test description cause I ain't understand where this function is called");
}

FText UQuestSystemGraphNode_Branch::GetNodeCategory_Implementation() const
{
    return LOCTEXT("QuestSystemGraphNode_BranchNodeCategory", "Branch Nodes");
}

FText UQuestSystemGraphNode_Branch::GetNodeTitle_Implementation() const
{
    return Super::GetNodeTitle_Implementation();
}

#undef LOCTEXT_NAMESPACE