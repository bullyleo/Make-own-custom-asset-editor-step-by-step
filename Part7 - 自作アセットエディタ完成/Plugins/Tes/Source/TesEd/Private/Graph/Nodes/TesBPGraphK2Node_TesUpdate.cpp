// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_TesUpdate.h"

#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"


void UTesBPGraphK2Node_TesUpdate::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	// ���s�s���̑���float�^�̃p�����[�^�s��������.
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Float, TEXT("DeltaSeconds"));
}

void UTesBPGraphK2Node_TesUpdate::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UE_LOG(LogTemp, Warning, TEXT("UTesBPGraphK2Node_TesUpdate::ExpandNode"));

	if (GetThenPin()->LinkedTo.Num() == 0)
	{
		return;
	}

	UEdGraphNode* FirstLogicNode = GetOutputNode();
	if (FirstLogicNode == nullptr)
		return;

	UK2Node_CustomEvent* EntryEventNode = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, nullptr, SourceGraph);
	EntryEventNode->bInternalEvent = true;
	EntryEventNode->CustomFunctionName = FName(TEXT("TesUpdate"));
	EntryEventNode->AllocateDefaultPins();

	// �p�����[�^�s�������m�[�h�͒ǉ��ł������̏������K�v.

	// ���̃m�[�h�����s�����ׂĂ����[�v.
	for (UEdGraphPin* OriginalParamPinOut : this->Pins)
	{
		// �o�̓s���ł͂Ȃ� �܂��� ���s�s���ł���
		if (OriginalParamPinOut->Direction != EGPD_Output || UEdGraphSchema_K2::IsExecPin(*OriginalParamPinOut))
		{
			// �X�L�b�v.
			continue;
		}

		// �p�����[�^�s���𐶐�.
		UEdGraphPin* NewParamPinOut = EntryEventNode->CreateUserDefinedPin(OriginalParamPinOut->PinName, OriginalParamPinOut->PinType, OriginalParamPinOut->Direction);
		check(NewParamPinOut);

		// �\�[�X�s������i���f�[�^��V�����s���ɃR�s�[����.
		NewParamPinOut->CopyPersistentDataFromOldPin(*OriginalParamPinOut);
		CompilerContext.MessageLog.NotifyIntermediatePinCreation(NewParamPinOut, OriginalParamPinOut);
	}

	// �J�X�^���C�x���g�m�[�h���č\��.
	EntryEventNode->ReconstructNode();


	const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();
	UEdGraphPin* EntryNodeOutPin = Schema->FindExecutionPin(*EntryEventNode, EGPD_Output);
	UEdGraphPin* ExecLogicInPin = Schema->FindExecutionPin(*FirstLogicNode, EGPD_Input);
	EntryNodeOutPin->MakeLinkTo(ExecLogicInPin);
	BreakAllNodeLinks();

	return;
}
