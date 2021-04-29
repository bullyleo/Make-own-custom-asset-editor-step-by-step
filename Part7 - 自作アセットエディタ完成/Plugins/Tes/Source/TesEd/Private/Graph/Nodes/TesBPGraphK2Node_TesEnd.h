// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_LogicEntry.h"
#include "TesBPGraphK2Node_TesEnd.generated.h"

/**
 * ì‡óeÇÕÅuUTesBPGraphK2Node_TesBeginÅvÇ∆ìØÇ∂.
 */
UCLASS()
class UTesBPGraphK2Node_TesEnd : public UTesBPGraphK2Node_LogicEntry
{
	GENERATED_BODY()

public:
	// UEdGraphNode
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	// ~UedGraphNode

};
