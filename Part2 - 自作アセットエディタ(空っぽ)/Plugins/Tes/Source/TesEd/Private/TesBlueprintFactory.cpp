// Fill out your copyright notice in the Description page of Project Settings.


#include "TesBlueprintFactory.h"
#include "TesInstance.h"
#include "Blueprints/TesBlueprint.h"

#include "Misc/MessageDialog.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "TesBlueprintFactory"

UTesBlueprintFactory::UTesBlueprintFactory()
{
	// アセットは生成可能です.
	bCreateNew = true;
	// アセット生成後はアセットが関連するエディタを開けます.
	bEditAfterNew = true;
	// 生成するアセットのクラス情報(リフレクション).
	SupportedClass = UTesBlueprint::StaticClass();

	ParentClass = UTesInstance::StaticClass();
}

UObject* UTesBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	// 生成可能かチェック.
	bool IsValidParentClass = ParentClass != nullptr;
	bool CanCreateBlueprint = FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass);
	bool IsChildOfParentClass = ParentClass->IsChildOf(UTesInstance::StaticClass());
	if (!IsValidParentClass || !CanCreateBlueprint || !IsChildOfParentClass)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), (ParentClass != NULL) ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("CannotCreateTesAssetBlueprint", "Cannot create a Tes Asset Blueprint based on the class '{ClassName}'."), Args));
		return nullptr;
	}

	// アセットの生成.(このファクトリが「アセット」と呼ぶのはUTesBlueprintのこと)
	UTesBlueprint* NewTesAssetBP = CastChecked<UTesBlueprint>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, EBlueprintType::BPTYPE_Normal, UTesBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext));

	return NewTesAssetBP;
}

UObject* UTesBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

#undef LOCTEXT_NAMESPACE
