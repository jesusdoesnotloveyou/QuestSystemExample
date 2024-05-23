// Quest System by JDNLY. All Rights Reserved

#include "AssetEditor/AssetQuestEditorToolbar.h"
#include "AssetEditor/AssetEditor_QuestSystemEditor.h"

#define LOCTEXT_NAMESPACE "AssetQuestEditorToolbar"

void FAssetQuestEditorToolbar::AddQuestEditorToolbar(TSharedPtr<FExtender> Extender)
{
    TSharedPtr<FAssetEditor_QuestSystemEditor> QuestEditorPtr = QuestEditor.Pin();
    check(QuestEditorPtr);

    TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
    ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, QuestEditorPtr->GetToolkitCommands(),
        FToolBarExtensionDelegate::CreateSP(this, &FAssetQuestEditorToolbar::FillQuestEditorToolbar));
    QuestEditorPtr->AddToolbarExtender(ToolbarExtender);
}

void FAssetQuestEditorToolbar::FillQuestEditorToolbar(FToolBarBuilder& ToolbarBuilder)
{
    TSharedPtr<FAssetEditor_QuestSystemEditor> QuestEditorPtr = QuestEditor.Pin();
    check(QuestEditorPtr);
    
    ToolbarBuilder.BeginSection("ExtendToolbarItem");
    {
        const FText NewNodeLabel = LOCTEXT("NewNode_Label", "New");
        const FText NewNodeTooltip = LOCTEXT("NewNode_ToolTip", "Create a new node");
        const FSlateIcon NewNodeIcon = FSlateIcon(TEXT("EditorStyle"), "SessionConsole.Clear");

        ToolbarBuilder.AddToolBarButton(
            FUIAction(
                FExecuteAction::CreateSP(QuestEditorPtr.Get(), &FAssetEditor_QuestSystemEditor::CreateNewNode),
                FCanExecuteAction::CreateSP(QuestEditorPtr.Get(), &FAssetEditor_QuestSystemEditor::CanCreateNewNode),
                FIsActionChecked()
            ),
            NAME_None,
            NewNodeLabel,
            NewNodeTooltip,
            NewNodeIcon
        );
    }
    ToolbarBuilder.EndSection();
    
    ToolbarBuilder.BeginSection("TestSection");
    {
        const FText TestLabel = LOCTEXT("TestButton_Label", "New Test");
        const FText TestTooltip = LOCTEXT("TestButton_ToolTip", "Test buttom");
        const FSlateIcon TestIcon = FSlateIcon(TEXT("EditorStyle"), "Automation.Warning");

        ToolbarBuilder.AddToolBarButton(
            FUIAction(),
            NAME_None,
            TestLabel,
            TestTooltip,
            TestIcon
        );
    }
    ToolbarBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE