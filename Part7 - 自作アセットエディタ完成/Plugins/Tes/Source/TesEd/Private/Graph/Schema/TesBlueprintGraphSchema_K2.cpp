// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Schema/TesBlueprintGraphSchema_K2.h"
#include "Graph/Nodes/TesBPGraphK2Node_TesBegin.h"
#include "Graph/Nodes/TesBPGraphK2Node_TesUpdate.h"
#include "Graph/Nodes/TesBPGraphK2Node_TesEnd.h"

#include "K2Node_CallFunction.h"
#include "Classes/EditorStyleSettings.h"


const FName UTesBlueprintGraphSchema_K2::GN_TesBlueprintDefinitionGraph(TEXT("TesBlueprintGraph"));


void UTesBlueprintGraphSchema_K2::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	// TesBeginノードの生成.
	FGraphNodeCreator<UTesBPGraphK2Node_TesBegin> TesBeginNodeCreator(Graph);
	UTesBPGraphK2Node_TesBegin* TesBeginNode = TesBeginNodeCreator.CreateNode();
	TesBeginNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);
	TesBeginNodeCreator.Finalize();
	SetNodeMetaData(TesBeginNode, FNodeMetadata::DefaultGraphNode);


	// TesUpdateノードの生成.
	FGraphNodeCreator<UTesBPGraphK2Node_TesUpdate> TesUpdateNodeCreator(Graph);
	UTesBPGraphK2Node_TesUpdate* TesUpdateNode = TesUpdateNodeCreator.CreateNode();
	TesUpdateNode->NodePosY = TesBeginNode->NodePosY + 400;
	TesUpdateNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);
	TesUpdateNode->MakeAutomaticallyPlacedGhostNode();	// ゴーストノード(半透明のやつ)とする. http://rarihoma.xvs.jp/2017/12/10/1/333
	TesUpdateNodeCreator.Finalize();
	SetNodeMetaData(TesUpdateNode, FNodeMetadata::DefaultGraphNode);


	// TesEndノードの生成.
	FGraphNodeCreator<UTesBPGraphK2Node_TesEnd> TesEndNodeCreator(Graph);
	UTesBPGraphK2Node_TesEnd* TesEndNode = TesEndNodeCreator.CreateNode();
	TesEndNode->NodePosY = TesUpdateNode->NodePosY + 400;
	TesEndNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);
	TesEndNode->MakeAutomaticallyPlacedGhostNode();
	TesEndNodeCreator.Finalize();
	SetNodeMetaData(TesEndNode, FNodeMetadata::DefaultGraphNode);

}
