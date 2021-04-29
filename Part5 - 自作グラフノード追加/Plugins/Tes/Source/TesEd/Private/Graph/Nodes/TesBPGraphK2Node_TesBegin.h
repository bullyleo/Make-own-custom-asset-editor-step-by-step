// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_LogicEntry.h"
#include "TesBPGraphK2Node_TesBegin.generated.h"

/**
 * �uBegin Play�v�Ǝ�������������.
 * TesComponent::RunTesInstance�Ăяo�����Ɏ��s�����.
 */
UCLASS()
class UTesBPGraphK2Node_TesBegin : public UTesBPGraphK2Node_LogicEntry
{
	GENERATED_BODY()

public:
	// UEdGraphNode

	// ���̃m�[�h���f�t�H���g�Ŕ�����s���𐶐�.
	virtual void AllocateDefaultPins() override;

	// ~UedGraphNode
};
