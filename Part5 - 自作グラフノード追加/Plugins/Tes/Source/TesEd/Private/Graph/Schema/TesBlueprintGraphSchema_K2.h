// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "TesBlueprintGraphSchema_K2.generated.h"

/**
 * �O���t�X�L�[�}:�O���t���ł̃��[�U�[�̑���(�E�N���b�N���̃R���e�L�X�g���j���[�\���A�m�[�h�̃��C���[�ڑ���)���`����.
 */
UCLASS()
class UTesBlueprintGraphSchema_K2 : public UEdGraphSchema_K2
{
	GENERATED_BODY()

public:
	// GN:Graph Name
	static const FName GN_TesBlueprintDefinitionGraph;

public:
	// UEdGraphSchema
	// TesBlueprintGraph�������Ƀf�t�H���g�Ŕz�u����Ă���ׂ��m�[�h�𐶐�.
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	// ~UEdGraphSchema
};
