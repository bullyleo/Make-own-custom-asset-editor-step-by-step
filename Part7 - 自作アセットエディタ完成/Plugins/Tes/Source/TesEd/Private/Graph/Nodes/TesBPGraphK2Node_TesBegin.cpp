// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_TesBegin.h"

#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"


void UTesBPGraphK2Node_TesBegin::AllocateDefaultPins()
{
	// �o�͑��̎��s�s���݂̂������.(�o�͑��̎��s�s���͊���Ƃ��āuPN_Then�v���g��)
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}


void UTesBPGraphK2Node_TesBegin::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UE_LOG(LogTemp, Warning, TEXT("UTesBPGraphK2Node_TesBegin::ExpandNode"));

	// ���s�s���������q�����Ă��Ȃ��Ȃ�A�Ȃɂ����Ȃ�.
	if (!GetOutputNode())
	{
		return;
	}

	// ���s�s������A�Ȃ�ŏ��̃m�[�h���擾.
	UEdGraphNode* FirstLogicNode = GetOutputNode();
	if (FirstLogicNode == nullptr)
		return;

	// ��������UTesBPGraphK2Node_TesBegin�m�[�h�ƃJ�X�^���C�x���g�m�[�h��u�������鏈��.

	// �J�X�^���C�x���g�m�[�h�𐶐�.���ꂪ���ۂ̃G���g���[�m�[�h�ƂȂ�.
	// �J�X�^���C�x���g�m�[�h�𐶐����邱�ƂŁA[CustomFunctionName]�Ƃ����֐��������֐��I�u�W�F�N�g����������
	// FindFunction�֐��Ō������邱�Ƃ��\�ƂȂ�.
	// ���ۂ�TesBegin�m�[�h�Ɍq���鏈�����Ăяo���d�g�݂́uUTesInstance�v�����邱��.
	UK2Node_CustomEvent* EntryEventNode = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, nullptr, SourceGraph);
	// �����@�\�p�̃C�x���g�Ȃ̂ŁA�Ăяo���s�ɂ���.
	EntryEventNode->bInternalEvent = true;
	EntryEventNode->CustomFunctionName = FName(TEXT("TesBegin"));	// �����Ɏw�肷�閼�O�͏d�����Ȃ����O�ɂ��邱��.NodeGuid���g���Ə��ǂ�.
	// �J�X�^���C�x���g�̃f�t�H���g�s���𐶐�.
	EntryEventNode->AllocateDefaultPins();

	const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();
	// EntryEventNode�̏o�̓s�����擾.
	UEdGraphPin* EntryNodeOutPin = Schema->FindExecutionPin(*EntryEventNode, EGPD_Output);
	// FirstLogicNode�m�[�h�̓��̓s�����擾.
	UEdGraphPin* ExecLogicInPin = Schema->FindExecutionPin(*FirstLogicNode, EGPD_Input);
	// �J�X�^���C�x���g�m�[�h��StateEntryNode�Ɍq����m�[�h�ƐV�����ڑ����쐬.
	EntryNodeOutPin->MakeLinkTo(ExecLogicInPin);
	// StateEntryNode�͂��ׂẴm�[�h�Ƃ̃����N��ڑ�����.(����Œu��������Ƃ���������)
	BreakAllNodeLinks();

	return;
}
