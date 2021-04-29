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
	// ���ۂɃA�Z�b�g�𐶐�����.
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	// ��Ɠ���.
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// �������̃f�t�H���g�A�Z�b�g��.
	virtual FString GetDefaultNewAssetName() const override { return "BP_TesAsset"; }
	// ~UFactory

private:
	// �n���ꂽ�u���[�v�����g�A�Z�b�g�ɑ΂���u�O���t�v�u�X�L�[�}�v�𐶐�����.
	void CreateGraphsForNewBlueprint(class UTesBlueprint* Blueprint);

private:
	// ��������u���[�v�����g�̐e�N���X.
	UPROPERTY()
		TSubclassOf<class UObject> ParentClass;
};
