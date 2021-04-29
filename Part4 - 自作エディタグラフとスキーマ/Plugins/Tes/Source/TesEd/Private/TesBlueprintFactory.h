// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "TesBlueprintFactory.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UTesBlueprintFactory : public UFactory
{
	GENERATED_BODY()
	
private:
	UTesBlueprintFactory();

	// UFactory
	// 実際にアセットを生成する.
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	// 上と同じ.
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// 生成時のデフォルトアセット名.
	virtual FString GetDefaultNewAssetName() const override { return "BP_TesAsset"; }
	// ~UFactory

private:
	// 渡されたブループリントアセットに対する「グラフ」「スキーマ」を生成する.
	void CreateGraphsForNewBlueprint(class UTesBlueprint* Blueprint);

private:
	// 生成するブループリントの親クラス.
	UPROPERTY()
		TSubclassOf<class UObject> ParentClass;
};
