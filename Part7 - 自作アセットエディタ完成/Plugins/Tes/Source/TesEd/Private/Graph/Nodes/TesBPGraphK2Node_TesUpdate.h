// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_LogicEntry.h"
#include "TesBPGraphK2Node_TesUpdate.generated.h"

/**
 * 
 */
UCLASS()
class UTesBPGraphK2Node_TesUpdate : public UTesBPGraphK2Node_LogicEntry
{
	GENERATED_BODY()

public:
	// UEdGraphNode
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	// ~UedGraphNode

};
