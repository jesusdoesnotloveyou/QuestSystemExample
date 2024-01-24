// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphEdge.h"

UQuestSystemGraphEdge::UQuestSystemGraphEdge()
{
	
}

UQuestSystemGraphEdge::~UQuestSystemGraphEdge()
{
	
}

UQuestSystemGraph* UQuestSystemGraphEdge::GetGraph() const
{
	return Graph;
}

#if WITH_EDITOR
void UQuestSystemGraphEdge::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}
#endif
