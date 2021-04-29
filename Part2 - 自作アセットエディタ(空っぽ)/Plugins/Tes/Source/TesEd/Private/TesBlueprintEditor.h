// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"

/**
 * TesBlueprintアセット用エディタ.
 * エディタ内で使用できるコマンド（コピー、ペースト、削除、複製等）を定義＆登録したりする.
 */
class FTesBlueprintEditor : public FBlueprintEditor
{
public:
	FTesBlueprintEditor() {}
	virtual ~FTesBlueprintEditor() {}

	void InitTesBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, class UTesBlueprint* Blueprint);

	//~ Begin IToolkit Interface
	// このツールキットの不変な名前を返す.
	virtual FName GetToolkitFName() const override { return FName("TesBlueprintEditor"); }
	// ローカライズされたツールキット名を返す.(通常は「editor」)
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("TesBlueprintEditor", "AppLabel", "Tes Blueprint Editor"); }
	// ローカライズされた、このツールキットのツールチップを返す.
	virtual FText GetToolkitToolTipText() const override { return FAssetEditorToolkit::GetToolTipTextForObject(GetBlueprintObj()); }
	// World-Centricモード時のローカライズされたタブラベルを返す.
	// World-Centric:レベルエディタの横にある、インターフェースを備えた世界中心のアセットエディタ.(APIより)
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("TesBlueprintEditor", "WorldCentricTabPrefix", "Tes Blueprint Editor ").ToString(); }
	// World-Centricモード時のタブラベルの色情報を返す.
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	//~ End IToolkit Interface

private:
	const FName TesBlueprintEditorName;
};