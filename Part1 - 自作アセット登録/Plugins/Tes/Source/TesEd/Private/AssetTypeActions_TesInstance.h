// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

/**
 * ���̃v���O�C�����񋟂���A�Z�b�g�ɑ΂���A�N�V�����̊��N���X.
 */
class FAssetTypeActions_TesBase : public FAssetTypeActions_Blueprint
{
public:
	FAssetTypeActions_TesBase(uint32 Categories);
	virtual uint32 GetCategories() override { return MyAssetCategory; }

protected:
	// �A�Z�b�g��������J�e�S��.(Add New���j���[��MyAssetCategory�ȉ��Ɋe�A�Z�b�g���\�������)
	uint32 MyAssetCategory;
};


/**
 * TesBlueprint�A�Z�b�g�ɑ΂���A�N�V�������`.
 */
class FAssetTypeActions_TesBlueprint : public FAssetTypeActions_TesBase
{
public:
	FAssetTypeActions_TesBlueprint(uint32 InAssetCategory);

	// FAssetTypeActions_Base
	// �A�Z�b�g���ږ�.(Add New���j���[�ŕ\������閼�O)
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions_TesBlueprint", "AssetTypeActions_TesBlueprint", "Tes Blueprint"); }
	// �A�Z�b�g�A�C�R���̔w�i�F.
	virtual FColor GetTypeColor() const override { return FColor(0, 128, 255); }
	// �A�Z�b�g���S������N���X.
	virtual UClass* GetSupportedClass() const override;
	// ~FAssetTypeActions_Base
};
