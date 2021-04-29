// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "TesBlueprintGraphSchema_K2.generated.h"

/**
 * グラフスキーマ:グラフ内でのユーザーの操作(右クリック時のコンテキストメニュー表示、ノードのワイヤー接続等)を定義する.
 */
UCLASS()
class UTesBlueprintGraphSchema_K2 : public UEdGraphSchema_K2
{
	GENERATED_BODY()

public:
	// GN:Graph Name
	static const FName GN_TesBlueprintDefinitionGraph;

public:
	// UEdGraphSchema
	// TesBlueprintGraph生成時にデフォルトで配置されているべきノードを生成.
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	// ~UEdGraphSchema
};
