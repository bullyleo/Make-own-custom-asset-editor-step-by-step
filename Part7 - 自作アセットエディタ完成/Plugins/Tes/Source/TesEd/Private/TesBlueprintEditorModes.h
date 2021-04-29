// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Kismet/Public/BlueprintEditorModes.h"


/**
 * アセットエディタの名前や編集モードの名前を保持する.
 */
struct FTesEditorModes
{
	// 一意のアセットエディタ名.
	static const FName TesEditorName;
	// 一意の編集モード名.
	static const FName TesBlueprintMode;

	static FText GetLocalizedMode(const FName InMode)
	{
		static TMap< FName, FText > LocModes;

		if (LocModes.Num() == 0)
		{
			LocModes.Add(TesBlueprintMode, NSLOCTEXT("TesEditorModes", "TesBlueprintMode", "Graph"));
		}

		check(InMode != NAME_None);
		const FText* OutDesc = LocModes.Find(InMode);
		check(OutDesc);
		return *OutDesc;
	}
private:
	FTesEditorModes() {}
};


/**
 * TesBlueprintアセットを編集するモード.
 * この編集モード時のアセットエディタレイアウトを定義する.
 */
class FTesBlueprintEditorMode : public FBlueprintEditorApplicationMode
{
public:
	FTesBlueprintEditorMode(TSharedPtr<class FTesBlueprintEditor> EditorIn);
	~FTesBlueprintEditorMode() {}
};
