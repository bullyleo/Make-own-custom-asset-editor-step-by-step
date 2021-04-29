// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_TesUpdate.h"

#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"


void UTesBPGraphK2Node_TesUpdate::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	// 実行ピンの他にfloat型のパラメータピンを持つ.
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Float, TEXT("DeltaSeconds"));
}

void UTesBPGraphK2Node_TesUpdate::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UE_LOG(LogTemp, Warning, TEXT("UTesBPGraphK2Node_TesUpdate::ExpandNode"));

	if (GetThenPin()->LinkedTo.Num() == 0)
	{
		return;
	}

	UEdGraphNode* FirstLogicNode = GetOutputNode();
	if (FirstLogicNode == nullptr)
		return;

	UK2Node_CustomEvent* EntryEventNode = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, nullptr, SourceGraph);
	EntryEventNode->bInternalEvent = true;
	EntryEventNode->CustomFunctionName = FName(TEXT("TesUpdate"));
	EntryEventNode->AllocateDefaultPins();

	// パラメータピンを持つノードは追加でいくつかの処理が必要.

	// このノードが持つピンすべてをループ.
	for (UEdGraphPin* OriginalParamPinOut : this->Pins)
	{
		// 出力ピンではない または 実行ピンである
		if (OriginalParamPinOut->Direction != EGPD_Output || UEdGraphSchema_K2::IsExecPin(*OriginalParamPinOut))
		{
			// スキップ.
			continue;
		}

		// パラメータピンを生成.
		UEdGraphPin* NewParamPinOut = EntryEventNode->CreateUserDefinedPin(OriginalParamPinOut->PinName, OriginalParamPinOut->PinType, OriginalParamPinOut->Direction);
		check(NewParamPinOut);

		// ソースピンから永続データを新しいピンにコピーする.
		NewParamPinOut->CopyPersistentDataFromOldPin(*OriginalParamPinOut);
		CompilerContext.MessageLog.NotifyIntermediatePinCreation(NewParamPinOut, OriginalParamPinOut);
	}

	// カスタムイベントノードを再構成.
	EntryEventNode->ReconstructNode();


	const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();
	UEdGraphPin* EntryNodeOutPin = Schema->FindExecutionPin(*EntryEventNode, EGPD_Output);
	UEdGraphPin* ExecLogicInPin = Schema->FindExecutionPin(*FirstLogicNode, EGPD_Input);
	EntryNodeOutPin->MakeLinkTo(ExecLogicInPin);
	BreakAllNodeLinks();

	return;
}
