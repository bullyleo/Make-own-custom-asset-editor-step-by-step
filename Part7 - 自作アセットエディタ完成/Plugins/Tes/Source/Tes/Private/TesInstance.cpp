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

	// ExpandNode関数で生成したCustomEventノードの「CustomFunctionName」に指定した文字列で関数オブジェクトを探す.
	// https://qiita.com/unknown_ds/items/30ea13c9d50f2c2de6ff
	// https://negimochi.work/ue4_findfunc/
	
	BeginFunc = FindFunction(TEXT("TesBegin"));
	UpdateFunc = FindFunction(TEXT("TesUpdate"));
	EndFunc = FindFunction(TEXT("TesEnd"));

	// ProcessEventに取得した関数オブジェクトを指定することで、その関数を実行することができる.
	// 第2引数には関数のパラメータ(引数)を表すデータを指定する.
	if(BeginFunc)
		ProcessEvent(BeginFunc, nullptr);
}

void UTesInstance::Update(float DeltaTime)
{
	if (UpdateFunc)
	{
		// パラメータはUE4では一般的に構造体を利用して値を渡す.
		FTesBlueprintUpdate_Parms Parms;
		Parms.DeltaTime = DeltaTime;
		ProcessEvent(UpdateFunc, &Parms);
	}
}

void UTesInstance::End()
{
	if (EndFunc)
	{
		ProcessEvent(EndFunc, nullptr);
	}
}

UWorld* UTesInstance::GetWorld() const
{
	return Context ? Context->GetWorld() : nullptr;
}
