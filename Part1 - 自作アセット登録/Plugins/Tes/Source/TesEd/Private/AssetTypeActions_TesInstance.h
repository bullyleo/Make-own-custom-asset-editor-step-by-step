// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

/**
 * このプラグインが提供するアセットに対するアクションの基底クラス.
 */
class FAssetTypeActions_TesBase : public FAssetTypeActions_Blueprint
{
public:
	FAssetTypeActions_TesBase(uint32 Categories);
	virtual uint32 GetCategories() override { return MyAssetCategory; }

protected:
	// アセットが属するカテゴリ.(Add NewメニューでMyAssetCategory以下に各アセットが表示される)
	uint32 MyAssetCategory;
};


/**
 * TesBlueprintアセットに対するアクションを定義.
 */
class FAssetTypeActions_TesBlueprint : public FAssetTypeActions_TesBase
{
public:
	FAssetTypeActions_TesBlueprint(uint32 InAssetCategory);

	// FAssetTypeActions_Base
	// アセット項目名.(Add Newメニューで表示される名前)
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions_TesBlueprint", "AssetTypeActions_TesBlueprint", "Tes Blueprint"); }
	// アセットアイコンの背景色.
	virtual FColor GetTypeColor() const override { return FColor(0, 128, 255); }
	// アセットが担当するクラス.
	virtual UClass* GetSupportedClass() const override;
	// ~FAssetTypeActions_Base
};
