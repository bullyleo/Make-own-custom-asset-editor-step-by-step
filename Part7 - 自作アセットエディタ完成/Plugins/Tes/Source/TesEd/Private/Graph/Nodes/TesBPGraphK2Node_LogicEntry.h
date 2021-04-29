// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_Base.h"
#include "TesBPGraphK2Node_LogicEntry.generated.h"

/**
 * グラフ上での具体的な処理(Print Stringノード等)とを繋ぐ、エントリーノード(入口)となるノードの基底クラス.
 */
UCLASS()
class UTesBPGraphK2Node_LogicEntry : public UTesBPGraphK2Node_Base
{
	GENERATED_BODY()

public:
	UTesBPGraphK2Node_LogicEntry();
};
