// Fill out your copyright notice in the Description page of Project Settings.


#include "TesInstance.h"


UTesInstance::UTesInstance()
	: Context(nullptr)
{}

void UTesInstance::Initialize(UObject* InContext)
{
	Context = InContext;
}

void UTesInstance::Start()
{
	UE_LOG(LogTemp, Warning, TEXT("UTesInstance::Start"));

	// ExpandNode�֐��Ő�������CustomEvent�m�[�h�́uCustomFunctionName�v�Ɏw�肵��������Ŋ֐��I�u�W�F�N�g��T��.
	// https://qiita.com/unknown_ds/items/30ea13c9d50f2c2de6ff
	// https://negimochi.work/ue4_findfunc/
	
	BeginFunc = FindFunction(TEXT("TesBegin"));

	// ProcessEvent�Ɏ擾�����֐��I�u�W�F�N�g���w�肷�邱�ƂŁA���̊֐������s���邱�Ƃ��ł���.
	// ��2�����ɂ͊֐��̃p�����[�^(����)��\���f�[�^���w�肷��.
	if(BeginFunc)
		ProcessEvent(BeginFunc, nullptr);
}

UWorld* UTesInstance::GetWorld() const
{
	return Context ? Context->GetWorld() : nullptr;
}
