// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/AssetQuestSystemGraphSchema.h"

#include "GraphEditorActions.h"
#include "QuestSystemGraph.h"
#include "QuestSystemGraphNode.h"
#include "ToolMenus.h"
#include "QuestSystemGraphAssetEditor/EdGraph_QuestSystemGraph.h"
#include "QuestSystemGraphAssetEditor/EdGraphNode_QuestSystemGraphNode.h"
#include "QuestSystemGraphAssetEditor/EdNodeEdge_QuestSystemGraphEdge.h"
#include "Framework/Commands/GenericCommands.h"
#include "Classes/EditorStyleSettings.h"
#include "QuestSystemGraphAssetEditor/ConnectionDrawingPolicy_QSG.h"

#define LOCTEXT_NAMESPACE "AssetSchema_QuestSystemEditor"

int32 UAssetQuestSystemGraphSchema::CurrentCacheRefreshID = 0;

class FNodeVisitorCycleChecker
{
public:
	/** Check whether a loop in the graph would be caused by linking the passed-in nodes */
	bool CheckForLoop(UEdGraphNode* StartNode, UEdGraphNode* EndNode)
	{
		VisitedNodes.Add(StartNode);
		return TraverseNodes(EndNode);
	}

private:
	bool TraverseNodes(UEdGraphNode* Node)
	{
		VisitedNodes.Add(Node);

		for (auto Pin : Node->Pins)
		{
			if (Pin->Direction == EGPD_Output)
			{
				for (auto OtherPin : Pin->LinkedTo)
				{
					UEdGraphNode* OtherNode = OtherPin->GetOwningNode();
					if (VisitedNodes.Contains(OtherNode))
					{
						// Only  an issue if this is a back-edge
						return false;
						return false;
					}
					else if (!FinishedNodes.Contains(OtherNode))
					{
						// Only should traverse if this node hasn't been traversed
						if (!TraverseNodes(OtherNode)) return false;
					}
				}
			}
		}

		VisitedNodes.Remove(Node);
		FinishedNodes.Add(Node);
		return true;
	};
	
	TSet<UEdGraphNode*> VisitedNodes;
	TSet<UEdGraphNode*> FinishedNodes;
};

void FQuestSystemEdGraphSchemaAction_NewNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

UEdGraphNode* FQuestSystemEdGraphSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = nullptr;
	// If there is a template, we actually use it
	if (NodeTemplate)
    {
    	const FScopedTransaction Transaction(LOCTEXT("AddNewNode", "Add New Node"));
    	ParentGraph->Modify();
    	if (FromPin) FromPin->Modify();

    	//NodeTemplate->SetFlags(RF_Transactional);
	    
	    // set outer to be the graph so it doesn't go away
    	NodeTemplate->Rename(nullptr, ParentGraph);
    	ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);
	    
    	NodeTemplate->CreateNewGuid();
    	NodeTemplate->PostPlacedNewNode();

    	NodeTemplate->NodePosX = Location.X;
    	NodeTemplate->NodePosY = Location.Y;
	    //ResultNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);

	    // there is mistake begins somewhere from 91 line  
    	NodeTemplate->QuestSystemGraphNode->SetFlags(RF_Transactional);
	    // might be here too
	    NodeTemplate->AllocateDefaultPins();
	    NodeTemplate->AutowireNewNode(FromPin);

    	ResultNode = NodeTemplate;
    }

    return ResultNode;
}

UEdGraphNode* FQuestSystemEdGraphSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
{
    UEdGraphNode* ResultNode;
    if (FromPins.Num() > 0)
    {
        ResultNode = PerformAction(ParentGraph, FromPins[0], Location);

        // Try autowiring the rest of the pins
        for (int32 Index = 1; Index < FromPins.Num(); ++Index)
        {
            ResultNode->AutowireNewNode(FromPins[Index]);
        }
    }
    else
    {
        ResultNode = PerformAction(ParentGraph, nullptr, Location, bSelectNewNode);
    }

    return ResultNode;
}

/////////////////////////////////////////////////////
// UEdGraphSchema

//TODO: 
void UAssetQuestSystemGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UQuestSystemGraph* Graph = CastChecked<UQuestSystemGraph>(ContextMenuBuilder.CurrentGraph->GetOuter());
	if (!Graph->NodeType) return;

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);

	const FText AddToolTip = LOCTEXT("NewQuestSystemGraphNodeTooltip", "Add node here");

	TSet<TSubclassOf<UQuestSystemGraphNode>> Visited;

	FText Desc = Graph->NodeType.GetDefaultObject()->ContextMenuName;

	if (Desc.IsEmpty())
	{
		FString Title = Graph->NodeType->GetName();
		Title.RemoveFromEnd("_C");
		Desc = FText::FromString(Title);
	}

	if (!Graph->NodeType->HasAnyClassFlags(CLASS_Abstract))
	{
		// TSharedPtr<FQuestSystemEdGraphSchemaAction_NewNode> TestNewNodeAction = AddNewNodeAction(ContextMenuBuilder, LOCTEXT("QuestSystemGraphNodeAction", "Quest System Graph Node"), Desc, FText());
	    // TestNewNodeAction->NodeTemplate = NewObject<UEdGraphNode_QuestSystemGraphNode>(ContextMenuBuilder.OwnerOfTemporaries);
	    // TestNewNodeAction->NodeTemplate->QuestSystemGraphNode = NewObject<UQuestSystemGraphNode>(TestNewNodeAction->NodeTemplate, Graph->NodeType);
		// TestNewNodeAction->NodeTemplate->QuestSystemGraphNode->Graph = Graph;
		TSharedPtr<FQuestSystemEdGraphSchemaAction_NewNode> NewNodeAction(new FQuestSystemEdGraphSchemaAction_NewNode(LOCTEXT("QuestSystemGraphNodeAction", "Quest System Graph Node"), Desc, AddToolTip, 0));
		NewNodeAction->NodeTemplate = NewObject<UEdGraphNode_QuestSystemGraphNode>(ContextMenuBuilder.OwnerOfTemporaries);
		NewNodeAction->NodeTemplate->QuestSystemGraphNode = NewObject<UQuestSystemGraphNode>(NewNodeAction->NodeTemplate, Graph->NodeType);
		NewNodeAction->NodeTemplate->QuestSystemGraphNode->Graph = Graph;
		ContextMenuBuilder.AddAction(NewNodeAction);

		Visited.Add(Graph->NodeType);
	}

	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(Graph->NodeType) && !It->HasAnyClassFlags(CLASS_Abstract) && !Visited.Contains(*It))
		{
			TSubclassOf<UQuestSystemGraphNode> NodeType = *It;

			if (It->GetName().StartsWith("REINST") || It->GetName().StartsWith("SKEL"))
				continue;

			if (!Graph->GetClass()->IsChildOf(NodeType.GetDefaultObject()->CompatibleGraphType))
				continue;

			Desc = NodeType.GetDefaultObject()->ContextMenuName;

			if (Desc.IsEmpty())
			{
				FString Title = NodeType->GetName();
				Title.RemoveFromEnd("_C");
				Desc = FText::FromString(Title);
			}

		    // TSharedPtr<FQuestSystemEdGraphSchemaAction_NewNode> TestNewNodeAction = AddNewNodeAction(ContextMenuBuilder, LOCTEXT("QuestSystemGraphNodeAction", "Quest System Graph Node"), Desc, FText());
		    // TestNewNodeAction->NodeTemplate = NewObject<UEdGraphNode_QuestSystemGraphNode>(ContextMenuBuilder.OwnerOfTemporaries);
		    // TestNewNodeAction->NodeTemplate->QuestSystemGraphNode = NewObject<UQuestSystemGraphNode>(TestNewNodeAction->NodeTemplate, Graph->NodeType);
		    // TestNewNodeAction->NodeTemplate->QuestSystemGraphNode->Graph = Graph;
			TSharedPtr<FQuestSystemEdGraphSchemaAction_NewNode> Action(new FQuestSystemEdGraphSchemaAction_NewNode(LOCTEXT("QuestSystemGraphNodeAction", "Quest System Graph Node"), Desc, AddToolTip, 0));
			Action->NodeTemplate = NewObject<UEdGraphNode_QuestSystemGraphNode>(ContextMenuBuilder.OwnerOfTemporaries);
			Action->NodeTemplate->QuestSystemGraphNode = NewObject<UQuestSystemGraphNode>(Action->NodeTemplate, NodeType);
			Action->NodeTemplate->QuestSystemGraphNode->Graph = Graph;
			ContextMenuBuilder.AddAction(Action);

			Visited.Add(NodeType);
		}
	}
}

void UAssetQuestSystemGraphSchema::GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	if (Context->Pin)
	{
		{
			FToolMenuSection& PinActionsSection = Menu->AddSection("GenericGraphAssetGraphSchemaNodeActions", LOCTEXT("PinActionsMenuHeader", "Pin Actions"));
			// Only display the 'Break Links' option if there is a link to break!
			if (Context->Pin->LinkedTo.Num() > 0)
			{
				PinActionsSection.AddMenuEntry(FGraphEditorCommands::Get().BreakPinLinks);
	
				// // add sub menu for break link to
				// if (Context->Pin->LinkedTo.Num() > 1)
				// {
				// 	PinActionsSection.AddSubMenu(
				// 		"BreakLinkTo",
				// 		LOCTEXT("BreakLinkTo", "Break Link To..."),
				// 		LOCTEXT("BreakSpecificLinks", "Break a specific link..."),
				// 		FNewToolMenuDelegate::CreateUObject((UAssetQuestSystemGraphSchema* const)this, &UAssetQuestSystemGraphSchema::GetBreakLinkToSubMenuActions, const_cast<UEdGraphPin*>(Context->Pin)));
				// }
				// else
				// {
				// 	((UAssetQuestSystemGraphSchema* const)this)->GetBreakLinkToSubMenuActions(Menu, const_cast<UEdGraphPin*>(Context->Pin));
				// }
			}
		}
	}
	if (Context->Node && !Context->Pin)
	{
		{
			FToolMenuSection& NodeActionsSection = Menu->AddSection("QuestSystemGraphSchemaNodeActions", LOCTEXT("ClassActionsMenuHeader", "Node Actions"));
			NodeActionsSection.AddMenuEntry(FGenericCommands::Get().Delete);
			NodeActionsSection.AddMenuEntry(FGenericCommands::Get().Cut);
			NodeActionsSection.AddMenuEntry(FGenericCommands::Get().Copy);
			NodeActionsSection.AddMenuEntry(FGenericCommands::Get().Duplicate);
			NodeActionsSection.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);

		    const UEdGraphNode_QuestSystemGraphNode* QuestNode = Cast<UEdGraphNode_QuestSystemGraphNode>(Context->Node);

		    if (QuestNode && QuestNode->CanPlaceBreakpoints())
		    {
		        FToolMenuSection& BreakpointSection = Menu->AddSection("QuestSystemGraphSchemaBreakpointActions", LOCTEXT("ClassActionsMenuHeader", "Breakpoint Actions"));
		        BreakpointSection.AddMenuEntry(FGraphEditorCommands::Get().ToggleBreakpoint);
		        BreakpointSection.AddMenuEntry(FGraphEditorCommands::Get().AddBreakpoint);
		        BreakpointSection.AddMenuEntry(FGraphEditorCommands::Get().RemoveBreakpoint);
		        BreakpointSection.AddMenuEntry(FGraphEditorCommands::Get().EnableBreakpoint);
		        BreakpointSection.AddMenuEntry(FGraphEditorCommands::Get().DisableBreakpoint);
		    }
		}
	}
	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UAssetQuestSystemGraphSchema::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
 //    UEdGraphNode_QuestSystemGraphNode* OutEdNode = Cast<UEdGraphNode_QuestSystemGraphNode>(PinA->GetOwningNode());
 //    UEdGraphNode_QuestSystemGraphNode* InEdNode = Cast<UEdGraphNode_QuestSystemGraphNode>(PinB->GetOwningNode());
 //
 //    // Determine if we can have cycles or not
 //    bool bAllowCycles = false;
 //    const auto EdGraph = Cast<UEdGraph_QuestSystemGraph>(OutEdNode->GetGraph());
 //    if (EdGraph)
 //    {
 //        bAllowCycles = EdGraph->GetGenericGraph()->bCanBeCyclical;
 //    }
 //
 //    // Check for cycles
 //    FNodeVisitorCycleChecker CycleChecker;
 //    if (!bAllowCycles && !CycleChecker.CheckForLoop(OutEdNode, InEdNode))
 //    {
 //    	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorCycle", "Can't create a graph cycle"));
 //    }
 //
 //    FText ErrorMessage;
 //    if (!OutEdNode->QuestSystemGraphNode->CanCreateConnectionTo(InEdNode->QuestSystemGraphNode, OutEdNode->GetOutputPin()->LinkedTo.Num(), ErrorMessage))
 //    {
 //    	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
 //    }
 //    if (!InEdNode->QuestSystemGraphNode->CanCreateConnectionFrom(OutEdNode->QuestSystemGraphNode, InEdNode->GetInputPin()->LinkedTo.Num(), ErrorMessage))
 //    {
 //    	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
 //    }
 //
 //    if (OutEdNode->QuestSystemGraphNode->GetGraph()->bEdgeEnabled)
 //    {
 //    	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, LOCTEXT("PinConnect", "Connect nodes with edge"));
 //    }
 //    else
 //    {
 //    	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
 //    }

    if (!PinA->GetOwningNode() || !PinB->GetOwningNode())
    {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorValidation", "One of the nodes isn't valid"));
    }
    
    // Make sure the pins are not on the same node
    if (PinA->GetOwningNode() == PinB->GetOwningNode())
    {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode", "Both are on the same node"));
    }

    // Compare the directions
    if (PinA->Direction == PinB->Direction)
    {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorDirection", "Can't connect the same type pins"));
    }
    
    // Make sure the pins are not on the same node
    return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
}

const FPinConnectionResponse UAssetQuestSystemGraphSchema::CanMergeNodes(const UEdGraphNode* NodeA, const UEdGraphNode* NodeB) const
{
    // Make sure the nodes are not the same 
    if (NodeA == NodeB)
    {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both are the same node"));
    }

    return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""/*Merging disallowed by default*/));
}

bool UAssetQuestSystemGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
    // We don't actually care about the pin, we want the node that is being dragged between
    UEdGraphNode_QuestSystemGraphNode* NodeA = Cast<UEdGraphNode_QuestSystemGraphNode>(A->GetOwningNode());
    UEdGraphNode_QuestSystemGraphNode* NodeB = Cast<UEdGraphNode_QuestSystemGraphNode>(B->GetOwningNode());

    // Check that this edge doesn't already exist
    for (UEdGraphPin* TestPin : NodeA->GetOutputPin()->LinkedTo)
    {
        UEdGraphNode* ChildNode = TestPin->GetOwningNode();
        if (UEdNodeEdge_QuestSystemGraphEdge* EdNode_Edge = Cast<UEdNodeEdge_QuestSystemGraphEdge>(ChildNode))
        {
            ChildNode = EdNode_Edge->GetEndNode();
        }

        if (ChildNode == NodeB)
            return false;
    }

    if (NodeA && NodeB)
    {
        // Always create connections from node A to B, don't allow adding in reverse
        Super::TryCreateConnection(NodeA->GetOutputPin(), NodeB->GetInputPin());
        return true;
    }
    return false;
}

class FConnectionDrawingPolicy* UAssetQuestSystemGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect &InClippingRect, FSlateWindowElementList &InDrawElements, UEdGraph *InGraphObj) const
{
     return new FConnectionDrawingPolicy_QSG(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}


FLinearColor UAssetQuestSystemGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::Blue;
}

void UAssetQuestSystemGraphSchema::BreakNodeLinks(UEdGraphNode &TargetNode) const
{
    const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakNodeLinks", "Break Node Links"));
    Super::BreakNodeLinks(TargetNode);
}

void UAssetQuestSystemGraphSchema::BreakPinLinks(UEdGraphPin &TargetPin, bool bSendsNodeNotifcation) const
{
    const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakPinLinks", "Break Pin Links"));
    Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);
}

void UAssetQuestSystemGraphSchema::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
    const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakSinglePinLink", "Break Pin Link"));
    Super::BreakSinglePinLink(SourcePin, TargetPin);
}

TSharedPtr<FQuestSystemEdGraphSchemaAction_NewNode> UAssetQuestSystemGraphSchema::AddNewNodeAction(FGraphActionListBuilderBase& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip)
{
    const auto NewAction = MakeShareable<FQuestSystemEdGraphSchemaAction_NewNode>(new FQuestSystemEdGraphSchemaAction_NewNode(Category, MenuDesc, Tooltip, 0));
    ContextMenuBuilder.AddAction(NewAction);
    return NewAction;
}

bool UAssetQuestSystemGraphSchema::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
    return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UAssetQuestSystemGraphSchema::GetCurrentVisualizationCacheID() const
{
    return CurrentCacheRefreshID;
}

void UAssetQuestSystemGraphSchema::ForceVisualizationCacheClear() const
{
    ++CurrentCacheRefreshID;
}

#undef LOCTEXT_NAMESPACE