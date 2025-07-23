// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SCommonEditorViewportToolbarBase.h"

/**
 * 
 */
class QUESTSYSTEMEDITOR_API SQuestEditorViewportToolbar : public SCommonEditorViewportToolbarBase
{
public:
    SLATE_BEGIN_ARGS(SQuestEditorViewportToolbar) {}

    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InRealViewport);
    
};
