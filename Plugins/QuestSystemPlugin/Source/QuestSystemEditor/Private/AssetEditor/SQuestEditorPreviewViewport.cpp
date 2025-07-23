// // Quest System by JDNLY. All Rights Reserved
//
//
// #include "AssetEditor/SQuestEditorPreviewViewport.h"
// #include "AssetEditor/QuestSystemEditorViewportClient.h"
// #include "AssetEditor/SQuestEditorViewportToolbar.h"
//
// TSharedRef<SEditorViewport> SQuestEditorPreviewViewport::GetViewportWidget()
// {
//     return SharedThis(this);
// }
//
// TSharedPtr<FExtender> SQuestEditorPreviewViewport::GetExtenders() const
// {
//     TSharedPtr<FExtender> Result(MakeShareable(new FExtender()));
//     return Result;
// }
//
// void SQuestEditorPreviewViewport::OnFloatingButtonClicked()
// {
//     
// }
//
// TSharedRef<FEditorViewportClient> SQuestEditorPreviewViewport::MakeEditorViewportClient()
// {
//     LevelViewportClient = MakeShareable(new FQuestSystemEditorViewportClient());
//     LevelViewportClient->ViewportType = LVT_Perspective;
//     LevelViewportClient->bSetListenerPosition = false;
//
//     return LevelViewportClient.ToSharedRef();
//     
// }
//
// TSharedPtr<SWidget> SQuestEditorPreviewViewport::MakeViewportToolbar()
// {
//     return SNew(SQuestEditorViewportToolbar, SharedThis(this))
//         .Cursor(EMouseCursor::Default);
// }
