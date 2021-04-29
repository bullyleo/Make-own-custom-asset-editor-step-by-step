// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_TesEnd.h"

#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"


void UTesBPGraphK2Node_TesEnd::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

void UTesBPGraphK2Node_TesEnd::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UE_LOG(LogTemp, Warning, TEXT("UTesBPGraphK2Node_TesEnd::ExpandNode"));

	if (GetThenPin()->LinkedTo.Num() == 0)
	{
		return;
	}

	UEdGraphNode* FirstLogicNode = GetOutputNode();
	if (FirstLogicNode == nullptr)
		return;

	UK2Node_CustomEvent* EntryEventNode = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, nullptr, SourceGraph);
	EntryEventNode->bInternalEvent = true;
	EntryEventNode->CustomFunctionName = FName(TEXT("TesEnd"));
	EntryEventNode->AllocateDefaultPins();

	const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();
	UEdGraphPin* EntryNodeOutPin = Schema->FindExecutionPin(*EntryEventNode, EGPD_Output);
	UEdGraphPin* ExecLogicInPin = Schema->FindExecutionPin(*FirstLogicNode, EGPD_Input);
	EntryNodeOutPin->MakeLinkTo(ExecLogicInPin);
	BreakAllNodeLinks();

	return;
}
