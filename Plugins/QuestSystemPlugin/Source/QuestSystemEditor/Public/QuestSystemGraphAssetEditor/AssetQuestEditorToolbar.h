// Quest System by JDNLY. All Rights Reserved

#pragma once

#include "CoreMinimal.h"

class FAssetEditor_QuestSystemGraph;
class FToolBarBuilder;
class FExtender;

class QUESTSYSTEMEDITOR_API FAssetQuestEditorToolbar : public TSharedFromThis<FAssetQuestEditorToolbar>
{
public:
	FAssetQuestEditorToolbar(TSharedPtr<FAssetEditor_QuestSystemGraph> InQuestEditor)
	    : QuestEditor(InQuestEditor) {}
    
    void AddQuestEditorToolbar(TSharedPtr<FExtender> Extender);
    
private:
    void FillQuestEditorToolbar(FToolBarBuilder& ToolbarBuilder); 

protected:
    /** Weak pointer back to the blueprint editor tool that owns us */
    TWeakPtr<FAssetEditor_QuestSystemGraph> QuestEditor;
};
