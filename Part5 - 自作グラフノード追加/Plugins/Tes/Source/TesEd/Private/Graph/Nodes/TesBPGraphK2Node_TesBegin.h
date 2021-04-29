// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_LogicEntry.h"
#include "TesBPGraphK2Node_TesBegin.generated.h"

/**
 * 「Begin Play」と似た役割を持つ.
 * TesComponent::RunTesInstance呼び出し時に実行される.
 */
UCLASS()
class UTesBPGraphK2Node_TesBegin : public UTesBPGraphK2Node_LogicEntry
{
	GENERATED_BODY()

public:
	// UEdGraphNode

	// このノードがデフォルトで備えるピンを生成.
	virtual void AllocateDefaultPins() override;

	// ~UedGraphNode
};
