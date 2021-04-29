// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_TesBegin.h"

#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"


void UTesBPGraphK2Node_TesBegin::AllocateDefaultPins()
{
	// �o�͑��̎��s�s���݂̂������.(�o�͑��̎��s�s���͊���Ƃ��āuPN_Then�v���g��)
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}
