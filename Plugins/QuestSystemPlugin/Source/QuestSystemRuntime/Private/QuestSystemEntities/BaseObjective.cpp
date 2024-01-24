// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemEntities/BaseObjective.h"

bool UBaseObjective::IsCompleted() const
{
	return ObjectiveState ? true : false;
}