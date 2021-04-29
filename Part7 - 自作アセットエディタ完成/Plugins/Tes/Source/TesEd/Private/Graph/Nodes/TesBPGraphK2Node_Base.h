// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_Base.h"
#include "TesBPGraphK2Node_Base.generated.h"

/**
 * ����m�[�h���ׂĂ̊��N���X.
 * ���̃m�[�h(�܂��͌p�������m�[�h)�͂����܂ł������ڂ����̂��̂ł���A��̓I�ȏ����͎�������Ȃ�.
 * �����UEdGraphNode��UK2Node�����l.
 * 
 * �����O���t�m�[�h�ɋ�̓I�ȏ��������������ꍇ
 * ��̓I�ȏ���(�uHello World�v�ƃ��O�ɕ\�����铙)�͕ʓrBlueprintFunctionLibrary�Ɏ������Ă���
 * ExpandNode�֐��I�[�o�[���C�h����FunctionLibrary�ɒ�`�����֐������̃m�[�h�ƕR�t����.
 * �Q�l: https://neil3d.gitee.io/unreal/custom_bp_node.html
 */
UCLASS()
class UTesBPGraphK2Node_Base : public UK2Node
{
	GENERATED_BODY()

public:
	UTesBPGraphK2Node_Base();

	// ���[�e�B���e�B.
	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;
	virtual UEdGraphPin* GetThenPin() const;
	virtual UEdGraphNode* GetOutputNode() const;
	// ~���[�e�B���e�B.
};
