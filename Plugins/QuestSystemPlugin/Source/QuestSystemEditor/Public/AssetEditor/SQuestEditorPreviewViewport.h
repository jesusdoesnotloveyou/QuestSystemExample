// // Quest System by JDNLY. All Rights Reserved
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "SCommonEditorViewportToolbarBase.h"
// #include "SEditorViewport.h"
//
// /**
//  * 
//  */
// class QUESTSYSTEMEDITOR_API SQuestEditorPreviewViewport : SEditorViewport, ICommonEditorViewportToolbarInfoProvider
// {
// public:
//     SLATE_BEGIN_ARGS(SQuestEditorPreviewViewport);
//     SLATE_END_ARGS()
//
//     // ICommonEditorViewportToolbarInfoProvider interface
//     virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
//     virtual TSharedPtr<FExtender> GetExtenders() const override;
//     virtual void OnFloatingButtonClicked() override;
//
//     // Create viewport client and toolbar
//     // SEditorViewport interface
//     virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
//     virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
//     // End of SEditorViewport interface
//
// private:
//     TSharedPtr<FEditorViewportClient> LevelViewportClient;
// };
