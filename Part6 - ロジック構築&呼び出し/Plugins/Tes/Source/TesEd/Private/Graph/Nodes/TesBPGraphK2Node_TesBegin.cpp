// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_TesBegin.h"

#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"


void UTesBPGraphK2Node_TesBegin::AllocateDefaultPins()
{
	// 出力側の実行ピンのみを備える.(出力側の実行ピンは慣例として「PN_Then」を使う)
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}


void UTesBPGraphK2Node_TesBegin::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UE_LOG(LogTemp, Warning, TEXT("UTesBPGraphK2Node_TesBegin::ExpandNode"));

	// 実行ピンが何も繋がっていないなら、なにもしない.
	if (!GetOutputNode())
	{
		return;
	}

	// 実行ピンから連なる最初のノードを取得.
	UEdGraphNode* FirstLogicNode = GetOutputNode();
	if (FirstLogicNode == nullptr)
		return;

	// ここからUTesBPGraphK2Node_TesBeginノードとカスタムイベントノードを置き換える処理.

	// カスタムイベントノードを生成.これが実際のエントリーノードとなる.
	// カスタムイベントノードを生成することで、[CustomFunctionName]という関数名を持つ関数オブジェクトが生成され
	// FindFunction関数で検索することが可能となる.
	// 実際にTesBeginノードに繋がる処理を呼び出す仕組みは「UTesInstance」を見ること.
	UK2Node_CustomEvent* EntryEventNode = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, nullptr, SourceGraph);
	// 内部機構用のイベントなので、呼び出し不可にする.
	EntryEventNode->bInternalEvent = true;
	EntryEventNode->CustomFunctionName = FName(TEXT("TesBegin"));	// ここに指定する名前は重複しない名前にすること.NodeGuidを使うと尚良し.
	// カスタムイベントのデフォルトピンを生成.
	EntryEventNode->AllocateDefaultPins();

	const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();
	// EntryEventNodeの出力ピンを取得.
	UEdGraphPin* EntryNodeOutPin = Schema->FindExecutionPin(*EntryEventNode, EGPD_Output);
	// FirstLogicNodeノードの入力ピンを取得.
	UEdGraphPin* ExecLogicInPin = Schema->FindExecutionPin(*FirstLogicNode, EGPD_Input);
	// カスタムイベントノードとStateEntryNodeに繋がるノードと新しく接続を作成.
	EntryNodeOutPin->MakeLinkTo(ExecLogicInPin);
	// StateEntryNodeはすべてのノードとのリンクを接続する.(これで置き換え作業が完了する)
	BreakAllNodeLinks();

	return;
}
