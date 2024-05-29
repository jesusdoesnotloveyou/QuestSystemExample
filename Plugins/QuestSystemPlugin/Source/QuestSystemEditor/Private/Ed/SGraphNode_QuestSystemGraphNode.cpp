// Quest System by JDNLY. All Rights Reserved

#include "Ed/SGraphNode_QuestSystemGraphNode.h"

#include "GraphEditorSettings.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "SCommentBubble.h"
#include "Ed/EdGraphNode_QuestSystemGraphNode.h"
#include "EditorStyleSet.h"
#include "GraphEditorDragDropAction.h"
#include "SGraphPin.h"
#include "Ed/EdNode_QuestSystemGraphEdge.h"

class SQuestSystemGraphNodePin : public SGraphPin
{
public:
    SLATE_BEGIN_ARGS(SQuestSystemGraphNodePin) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
    {
        this->SetCursor(EMouseCursor::Default);

        bShowLabel = true;

        GraphPinObj = InPin;
        check(GraphPinObj);

        const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
        check(Schema);

        SBorder::Construct(SBorder::FArguments()
            .BorderImage(this, &SQuestSystemGraphNodePin::GetPinBorder)
            .BorderBackgroundColor(this, &SQuestSystemGraphNodePin::GetPinColor)
            .OnMouseButtonDown(this, &SQuestSystemGraphNodePin::OnPinMouseDown)
            .Cursor(this, &SQuestSystemGraphNodePin::GetPinCursor)
            .Padding(FMargin(5.0f))
        );
    }

protected:
    virtual FSlateColor GetPinColor() const override
    {
        return FSlateColor(FLinearColor(FColor::White));
    }

    virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
    {
        return SNew(STextBlock);
    }

    const FSlateBrush* GetPinBorder() const
    {
        return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
    }
};

void SGraphNode_QuestSystemGraphNode::Construct(const FArguments& InArgs, UEdGraphNode_QuestSystemGraphNode* InNode)
{
    SetCursor(EMouseCursor::CardinalCross);

    GraphNode = InNode;
    InNode->SEdNode = this;
    
	UpdateGraphNode();
}

void SGraphNode_QuestSystemGraphNode::UpdateGraphNode()
{
    InputPins.Empty();
    OutputPins.Empty();

    RightNodeBox.Reset();
    LeftNodeBox.Reset();
    TopNodeBox.Reset();
    BottomNodeBox.Reset();

    const FSlateBrush* NodeTypeIcon = GetNameIcon();

	FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);
	TSharedPtr<SErrorText> ErrorText;
	TSharedPtr<SVerticalBox> NodeBody;
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0.0f)
			.BorderBackgroundColor(this, &SGraphNode_QuestSystemGraphNode::GetBorderBackgroundColor)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)

					// Input Pin Area
					+ SVerticalBox::Slot()
					.FillHeight(1)
					[
						SAssignNew(LeftNodeBox, SVerticalBox)
					]

					// Output Pin Area	
					+ SVerticalBox::Slot()
					.FillHeight(1)
					[
						SAssignNew(RightNodeBox, SVerticalBox)
					]
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(8.0f)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.ColorSpill"))
					.BorderBackgroundColor(TitleShadowColor)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Visibility(EVisibility::SelfHitTestInvisible)
					.Padding(6.0f)
					[
						SAssignNew(NodeBody, SVerticalBox)
									
						// Title
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)

							// Error message
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SAssignNew(ErrorText, SErrorText)
								.BackgroundColor(this, &SGraphNode_QuestSystemGraphNode::GetErrorColor)
								.ToolTipText(this, &SGraphNode_QuestSystemGraphNode::GetErrorMsgToolTip)
							]

							// Icon
							+SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							[
								SNew(SImage)
								.Image(NodeTypeIcon)
							]
										
							// Node Title
							+ SHorizontalBox::Slot()
							.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SAssignNew(InlineEditableText, SInlineEditableTextBlock)
									.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
									.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
									.OnVerifyTextChanged(this, &SGraphNode_QuestSystemGraphNode::OnVerifyNameTextChanged)
									.OnTextCommitted(this, &SGraphNode_QuestSystemGraphNode::OnNameTextCommited)
									.IsReadOnly(this, &SGraphNode_QuestSystemGraphNode::IsNameReadOnly)
									.IsSelected(this, &SGraphNode_QuestSystemGraphNode::IsSelectedExclusively)
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									NodeTitle.ToSharedRef()
								]
							]
						]					
					]
				]
			]
		];

	// Create comment bubble
	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);
    
    // CreateNodeWidget();
    CreatePinWidgets();
    
    //SGraphNode::UpdateGraphNode();
}

void SGraphNode_QuestSystemGraphNode::CreatePinWidgets()
{
    UEdGraphNode_QuestSystemGraphNode* StateNode = CastChecked<UEdGraphNode_QuestSystemGraphNode>(GraphNode);

    for (int32 PinIdx = 0; PinIdx < StateNode->Pins.Num(); PinIdx++)
    {
        UEdGraphPin* CurPin = StateNode->Pins[PinIdx];
        if (!CurPin->bHidden)
        {
            TSharedPtr<SGraphPin> NewPin = SNew(SQuestSystemGraphNodePin, CurPin);

            AddPin(NewPin.ToSharedRef());
        }
    }
    
    //SGraphNode::CreatePinWidgets();
}

void SGraphNode_QuestSystemGraphNode::AddPin(const TSharedRef<SGraphPin> &PinToAdd)
{
    SGraphNode::AddPin(PinToAdd);
}

bool SGraphNode_QuestSystemGraphNode::IsNameReadOnly() const
{
    return SGraphNode::IsNameReadOnly();
}

FSlateColor SGraphNode_QuestSystemGraphNode::GetBorderBackgroundColor() const
{
    // More complex logic in Mountea or Generic
    return FSlateColor(FLinearColor(0.0f, 0.22f, 0.4f));
}

FSlateColor SGraphNode_QuestSystemGraphNode::GetBackgroundColor() const
{
    return FSlateColor(FLinearColor(0.1f, 0.1f, 0.1f));
}

EVisibility SGraphNode_QuestSystemGraphNode::GetGragOverMarkerVisibility()
{
    return EVisibility::Visible;
}

const FSlateBrush* SGraphNode_QuestSystemGraphNode::GetNameIcon() const
{
    return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
}
