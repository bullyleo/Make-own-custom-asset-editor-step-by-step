// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"

/**
 * TesBlueprint�A�Z�b�g�p�G�f�B�^.
 * �G�f�B�^���Ŏg�p�ł���R�}���h�i�R�s�[�A�y�[�X�g�A�폜�A�������j���`���o�^�����肷��.
 */
class FTesBlueprintEditor : public FBlueprintEditor
{
public:
	FTesBlueprintEditor() {}
	virtual ~FTesBlueprintEditor() {}

	void InitTesBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, class UTesBlueprint* Blueprint);

	//~ Begin IToolkit Interface
	// ���̃c�[���L�b�g�̕s�ςȖ��O��Ԃ�.
	virtual FName GetToolkitFName() const override { return FName("TesBlueprintEditor"); }
	// ���[�J���C�Y���ꂽ�c�[���L�b�g����Ԃ�.(�ʏ�́ueditor�v)
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("TesBlueprintEditor", "AppLabel", "Tes Blueprint Editor"); }
	// ���[�J���C�Y���ꂽ�A���̃c�[���L�b�g�̃c�[���`�b�v��Ԃ�.
	virtual FText GetToolkitToolTipText() const override { return FAssetEditorToolkit::GetToolTipTextForObject(GetBlueprintObj()); }
	// World-Centric���[�h���̃��[�J���C�Y���ꂽ�^�u���x����Ԃ�.
	// World-Centric:���x���G�f�B�^�̉��ɂ���A�C���^�[�t�F�[�X����������E���S�̃A�Z�b�g�G�f�B�^.(API���)
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("TesBlueprintEditor", "WorldCentricTabPrefix", "Tes Blueprint Editor ").ToString(); }
	// World-Centric���[�h���̃^�u���x���̐F����Ԃ�.
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	//~ End IToolkit Interface

private:
	const FName TesBlueprintEditorName;
};