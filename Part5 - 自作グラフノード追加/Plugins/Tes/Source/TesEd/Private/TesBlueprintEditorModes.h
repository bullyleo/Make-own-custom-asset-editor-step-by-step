// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Kismet/Public/BlueprintEditorModes.h"


/**
 * �A�Z�b�g�G�f�B�^�̖��O��ҏW���[�h�̖��O��ێ�����.
 */
struct FTesEditorModes
{
	// ��ӂ̃A�Z�b�g�G�f�B�^��.
	static const FName TesEditorName;
	// ��ӂ̕ҏW���[�h��.
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
 * TesBlueprint�A�Z�b�g��ҏW���郂�[�h.
 * ���̕ҏW���[�h���̃A�Z�b�g�G�f�B�^���C�A�E�g���`����.
 */
class FTesBlueprintEditorMode : public FBlueprintEditorApplicationMode
{
public:
	FTesBlueprintEditorMode(TSharedPtr<class FTesBlueprintEditor> EditorIn);
	~FTesBlueprintEditorMode() {}
};
