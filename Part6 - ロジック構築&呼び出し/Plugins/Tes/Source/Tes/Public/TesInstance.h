// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TesInstance.generated.h"	


// ProcessEvent関数呼び出し時に渡すパラメータ構造体.
struct FTesBlueprintUpdate_Parms
{
	float DeltaTime;	// 更新処理時のデルタ時間.
};

/**
 * アセットクラス.
 * TesBlueprintに記述した処理は、このクラスを通して実行される.
 * ユーザー側とエディタ(ブループリント)側の間に立つ、インターフェース(窓口)となる.
 * 
 * Tickについて：
 * FTickableGameObjectのTickは、ポーズ中でも止まらなかったので不採用.
 * Behavior Treeの仕組みと同様にActor Componentの初期化、更新、終了を利用する方針を取った.
 */
UCLASS(Blueprintable, BlueprintType)
class TES_API UTesInstance : public UObject
{
	GENERATED_BODY()

private:
	UFunction* BeginFunc;	// 「TesBegin」関数オブジェクトを保持する.

	UPROPERTY()
		UObject* Context;

public:
	UTesInstance();

	// アセットクラスそのものの初期化処理.
	void Initialize(UObject* InContext);

	// TesBlueprintに記述した処理を呼び出す.
	void Start();

	// Print Stringノードのような「World Context」を要求するタイプのノードに対しコンテキストオブジェクトを提供する.
	// (これによってWorld Contextピンが非表示になる)
	virtual UWorld* GetWorld() const override;

};
