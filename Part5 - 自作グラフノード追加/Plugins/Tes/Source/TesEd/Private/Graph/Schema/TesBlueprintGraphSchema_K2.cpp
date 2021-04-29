// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Schema/TesBlueprintGraphSchema_K2.h"
#include "Graph/Nodes/TesBPGraphK2Node_TesBegin.h"

#include "K2Node_CallFunction.h"
#include "Classes/EditorStyleSettings.h"


const FName UTesBlueprintGraphSchema_K2::GN_TesBlueprintDefinitionGraph(TEXT("TesBlueprintGraph"));


void UTesBlueprintGraphSchema_K2::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	// TesBeginÉmÅ[ÉhÇÃê∂ê¨.
	FGraphNodeCreator<UTesBPGraphK2Node_TesBegin> TesBeginNodeCreator(Graph);
	UTesBPGraphK2Node_TesBegin* TesBeginNode = TesBeginNodeCreator.CreateNode();
	TesBeginNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);
	TesBeginNodeCreator.Finalize();
	SetNodeMetaData(TesBeginNode, FNodeMetadata::DefaultGraphNode);
}
