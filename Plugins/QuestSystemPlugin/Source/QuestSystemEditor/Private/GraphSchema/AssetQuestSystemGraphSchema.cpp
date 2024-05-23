// Quest System by JDNLY. All Rights Reserved

#include "GraphSchema/AssetQuestSystemGraphSchema.h"

#include "GraphEditorActions.h"
#include "QuestSystemGraph.h"
#include "QuestSystemGraphNode.h"
#include "ToolMenus.h"
#include "Ed/EdGraph_QuestSystemGraph.h"
#include "Ed/EdGraphNode_QuestSystemGraphNode.h"
#include "Ed/EdNode_QuestSystemGraphEdge.h"
#include "Framework/Commands/GenericCommands.h"
#include "Classes/EditorStyleSettings.h"
#include "QuestSystemGraphAssetEditor/ConnectionDrawingPolicy_QuestSystemEditor.h"

#define LOCTEXT_NAMESPACE "AssetSchema_QuestSystemEditor"

int32 UAssetQuestSystemGraphSchema::CurrentCacheRefreshID = 0;

namespace SchemaUtils
{
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
}

void FEdGraphSchemaAction_QuestSystemEditor_NewNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

UEdGraphNode* FEdGraphSchemaAction_QuestSystemEditor_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = nullptr;
	// If there is a template, we actually use it
	if (NodeTemplate)
    {
    	const FScopedTransaction Transaction(LOCTEXT("QuestSystemEditorNewNode", "Quest System Editor: New Node"));
    	ParentGraph->Modify();
    	if (FromPin) FromPin->Modify();
	    
	    // set outer to be the graph so it doesn't go away
    	NodeTemplate->Rename(nullptr, ParentGraph);
    	ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);
	    
    	NodeTemplate->CreateNewGuid();
    	NodeTemplate->PostPlacedNewNode();
	    NodeTemplate->AllocateDefaultPins();
	    NodeTemplate->AutowireNewNode(FromPin);

    	NodeTemplate->NodePosX = Location.X;
    	NodeTemplate->NodePosY = Location.Y;
	    //ResultNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);
	    
    	NodeTemplate->QuestSystemGraphNode->SetFlags(RF_Transactional);
	    NodeTemplate->SetFlags(RF_Transactional);
	        
    	ResultNode = NodeTemplate;
    }
    return ResultNode;
}

UEdGraphNode* FEdGraphSchemaAction_QuestSystemEditor_NewNode::PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
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

UEdGraphNode* FEdGraphSchemaAction_QuestSystemEditor_NewEdge::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
    UEdGraphNode* ResultNode = nullptr;
    // If there is a template, we actually use it
    if (NodeTemplate)
    {
        const FScopedTransaction Transaction(LOCTEXT("QuestSystemEditorNewEdge", "Quest System Editor: New Edge"));
        ParentGraph->Modify();
        if (FromPin) FromPin->Modify();
	    
        // set outer to be the graph so it doesn't go away
        NodeTemplate->Rename(nullptr, ParentGraph);
        ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);
	    
        NodeTemplate->CreateNewGuid();
        NodeTemplate->PostPlacedNewNode();
        NodeTemplate->AllocateDefaultPins();
        NodeTemplate->AutowireNewNode(FromPin);

        NodeTemplate->NodePosX = Location.X;
        NodeTemplate->NodePosY = Location.Y;
        //ResultNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);
	    
        NodeTemplate->QuestSystemGraphEdge->SetFlags(RF_Transactional);
        NodeTemplate->SetFlags(RF_Transactional);
	        
        ResultNode = NodeTemplate;
    }
    return ResultNode;
}

// UEdGraphNode* FEdGraphSchemaAction_QuestSystemEditor_NewEdge::PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode /*= true*/)
// {
//     
// }

void FEdGraphSchemaAction_QuestSystemEditor_NewEdge::AddReferencedObjects(FReferenceCollector& Collector)
{
    FEdGraphSchemaAction::AddReferencedObjects(Collector);
    Collector.AddReferencedObject(NodeTemplate);
}

/////////////////////////////////////////////////////
// UEdGraphSchema

void UAssetQuestSystemGraphSchema::GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin *InGraphPin)
{
    // Make sure we have a unique name for every entry in the list
    TMap< FString, uint32 > LinkTitleCount;

    FToolMenuSection& Section = Menu->FindOrAddSection("QuestSystemEditorAssetGraphSchemaPinActions");

    // Add all the links we could break from
    for (TArray<class UEdGraphPin*>::TConstIterator Links(InGraphPin->LinkedTo); Links; ++Links)
    {
        UEdGraphPin* Pin = *Links;
        FString TitleString = Pin->GetOwningNode()->GetNodeTitle(ENodeTitleType::ListView).ToString();
        FText Title = FText::FromString(TitleString);
        if (Pin->PinName != TEXT(""))
        {
            TitleString = FString::Printf(TEXT("%s (%s)"), *TitleString, *Pin->PinName.ToString());

            // Add name of connection if possible
            FFormatNamedArguments Args;
            Args.Add(TEXT("NodeTitle"), Title);
            Args.Add(TEXT("PinName"), Pin->GetDisplayName());
            Title = FText::Format(LOCTEXT("BreakDescPin", "{NodeTitle} ({PinName})"), Args);
        }

        uint32& Count = LinkTitleCount.FindOrAdd(TitleString);

        FText Description;
        FFormatNamedArguments Args;
        Args.Add(TEXT("NodeTitle"), Title);
        Args.Add(TEXT("NumberOfNodes"), Count);

        if (Count == 0)
        {
            Description = FText::Format(LOCTEXT("BreakDesc", "Break link to {NodeTitle}"), Args);
        }
        else
        {
            Description = FText::Format(LOCTEXT("BreakDescMulti", "Break link to {NodeTitle} ({NumberOfNodes})"), Args);
        }
        ++Count;

        Section.AddMenuEntry(NAME_None, Description, Description, FSlateIcon(), FUIAction(
            FExecuteAction::CreateUObject(this, &UAssetQuestSystemGraphSchema::BreakSinglePinLink, const_cast<UEdGraphPin*>(InGraphPin), *Links)));
    }
}


void UAssetQuestSystemGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UQuestSystemGraph* Graph = CastChecked<UQuestSystemGraph>(ContextMenuBuilder.CurrentGraph->GetOuter());
	if (!Graph->NodeType) return;

	const bool bNoParent = (ContextMenuBuilder.FromPin == nullptr);

	FText AddToolTip = LOCTEXT("NewQuestSystemGraphNodeTooltip", "Add node here");

	TSet<TSubclassOf<UQuestSystemGraphNode>> Visited;

	FText Desc = Graph->NodeType.GetDefaultObject()->ContextMenuName;
    FText NodeCategory = Graph->NodeType.GetDefaultObject()->GetNodeCategory();

	if (Desc.IsEmpty())
	{
		FString Title = Graph->NodeType->GetName();
		Title.RemoveFromEnd("_C");
		Desc = FText::FromString(Title);
	}

	if (!Graph->NodeType->HasAnyClassFlags(CLASS_Abstract))
	{
		TSharedPtr<FEdGraphSchemaAction_QuestSystemEditor_NewNode> NewNodeAction(new FEdGraphSchemaAction_QuestSystemEditor_NewNode(NodeCategory, Desc, AddToolTip, 0));
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

            // if (!NodeType.GetDefaultObject()->bAllowManualCreate)
            //     continue;
		    
			Desc = NodeType.GetDefaultObject()->ContextMenuName;
		    AddToolTip = NodeType.GetDefaultObject()->GetDescription();
		    NodeCategory = NodeType.GetDefaultObject()->GetNodeCategory();

			if (Desc.IsEmpty())
			{
				FString Title = NodeType->GetName();
				Title.RemoveFromEnd("_C");
				Desc = FText::FromString(Title);
			}
		    
			TSharedPtr<FEdGraphSchemaAction_QuestSystemEditor_NewNode> Action(new FEdGraphSchemaAction_QuestSystemEditor_NewNode(NodeCategory, Desc, AddToolTip, 0));
			Action->NodeTemplate = NewObject<UEdGraphNode_QuestSystemGraphNode>(ContextMenuBuilder.OwnerOfTemporaries);
			Action->NodeTemplate->QuestSystemGraphNode = NewObject<UQuestSystemGraphNode>(Action->NodeTemplate, NodeType);
			Action->NodeTemplate->QuestSystemGraphNode->Graph = Graph;
			ContextMenuBuilder.AddAction(Action);

			Visited.Add(NodeType);
		}
	}
}

EGraphType UAssetQuestSystemGraphSchema::GetGraphType(const UEdGraph *TestEdGraph) const
{
    return GT_StateMachine;
}

void UAssetQuestSystemGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Pin)
	{
		FToolMenuSection& PinActionsSection = Menu->AddSection("QuestSystemEditorAssetGraphSchemaNodeActions", LOCTEXT("PinActionsMenuHeader", "Pin Actions"));
		// Only display the 'Break Links' option if there is a link to break!
		if (Context->Pin->LinkedTo.Num() > 0)
		{
			PinActionsSection.AddMenuEntry(FGraphEditorCommands::Get().BreakPinLinks);

			// add sub menu for break link to
			if (Context->Pin->LinkedTo.Num() > 1)
			{
				PinActionsSection.AddSubMenu(
					"BreakLinkTo",
					LOCTEXT("BreakLinkTo", "Break Link To..."),
					LOCTEXT("BreakSpecificLinks", "Break a specific link..."),
					FNewToolMenuDelegate::CreateUObject((UAssetQuestSystemGraphSchema* const)this, &UAssetQuestSystemGraphSchema::GetBreakLinkToSubMenuActions, const_cast<UEdGraphPin*>(Context->Pin)));
			}
			else
			{
				((UAssetQuestSystemGraphSchema* const)this)->GetBreakLinkToSubMenuActions(Menu, const_cast<UEdGraphPin*>(Context->Pin));
			}
		}
	}
	if (Context->Node && !Context->Pin)
	{
		
		FToolMenuSection& NodeActionsSection = Menu->AddSection("QuestSystemGraphSchemaNodeActions", LOCTEXT("ClassActionsMenuHeader", "Node Actions"));
	    NodeActionsSection.AddSeparator(FName("Main Options"));
	    NodeActionsSection.AddMenuEntry(FGenericCommands::Get().Rename);
	    NodeActionsSection.AddSeparator(FName("Other Options"));
        NodeActionsSection.AddMenuEntry(FGenericCommands::Get().Rename);
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
 //    SchemaUtils::FNodeVisitorCycleChecker CycleChecker;
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
        if (UEdNode_QuestSystemGraphEdge* EdNode_Edge = Cast<UEdNode_QuestSystemGraphEdge>(ChildNode))
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

bool UAssetQuestSystemGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin *A, UEdGraphPin *B) const
{
        UEdGraphNode_QuestSystemGraphNode* NodeA = Cast<UEdGraphNode_QuestSystemGraphNode>(A->GetOwningNode());
    	UEdGraphNode_QuestSystemGraphNode* NodeB = Cast<UEdGraphNode_QuestSystemGraphNode>(B->GetOwningNode());
    
    	// Are nodes and pins all valid?
    	if (!NodeA || !NodeA->GetOutputPin() || !NodeB || !NodeB->GetInputPin()) return false;
    	
    	UQuestSystemGraph* Graph = NodeA->QuestSystemGraphNode->GetGraph();
    
    	FVector2D InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);
    
    	FEdGraphSchemaAction_QuestSystemEditor_NewEdge Action;
    	Action.NodeTemplate = NewObject<UEdNode_QuestSystemGraphEdge>(NodeA->GetGraph());
    	Action.NodeTemplate->SetEdge(NewObject<UQuestSystemGraphEdge>(Action.NodeTemplate, Graph->EdgeType));
    	UEdNode_QuestSystemGraphEdge* EdgeNode = Cast<UEdNode_QuestSystemGraphEdge>(Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));
    
    	// Always create connections from node A to B, don't allow adding in reverse
    	EdgeNode->CreateConnections(NodeA, NodeB);
    
    	return true;
}


// Connection policy registered in FQuestSystemEditorModule
// class FConnectionDrawingPolicy* UAssetQuestSystemGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect &InClippingRect, FSlateWindowElementList &InDrawElements, UEdGraph *InGraphObj) const
// {
//      return new FConnectionDrawingPolicy_QuestSystemEditor(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
// }


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

TSharedPtr<FEdGraphSchemaAction_QuestSystemEditor_NewNode> UAssetQuestSystemGraphSchema::AddNewNodeAction(FGraphActionListBuilderBase& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip)
{
    const auto NewAction = MakeShareable<FEdGraphSchemaAction_QuestSystemEditor_NewNode>(new FEdGraphSchemaAction_QuestSystemEditor_NewNode(Category, MenuDesc, Tooltip, 0));
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

void UAssetQuestSystemGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
    Super::CreateDefaultNodesForGraph(Graph);
}

#undef LOCTEXT_NAMESPACE