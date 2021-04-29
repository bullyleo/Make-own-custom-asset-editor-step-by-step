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
	// �A�Z�b�g�͐����\�ł�.
	bCreateNew = true;
	// �A�Z�b�g������̓A�Z�b�g���֘A����G�f�B�^���J���܂�.
	bEditAfterNew = true;
	// ��������A�Z�b�g�̃N���X���(���t���N�V����).
	SupportedClass = UTesBlueprint::StaticClass();

	ParentClass = UTesInstance::StaticClass();
}

UObject* UTesBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	// �����\���`�F�b�N.
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

	// �A�Z�b�g�̐���.(���̃t�@�N�g�����u�A�Z�b�g�v�ƌĂԂ̂�UTesBlueprint�̂���)
	UTesBlueprint* NewTesAssetBP = CastChecked<UTesBlueprint>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, EBlueprintType::BPTYPE_Normal, UTesBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext));

	return NewTesAssetBP;
}

UObject* UTesBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

#undef LOCTEXT_NAMESPACE
