// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TesInstance.generated.h"	


/**
 * アセットクラス.
 * TesBlueprintに記述した処理は、このクラスを通して実行される.
 * ユーザー側とエディタ(ブループリント)側の間に立つ、インターフェース(窓口)となる.
 */
UCLASS(Blueprintable, BlueprintType)
class TES_API UTesInstance : public UObject
{
	GENERATED_BODY()
};
