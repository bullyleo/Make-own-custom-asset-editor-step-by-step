// Fill out your copyright notice in the Description page of Project Settings.


#include "TesBlueprintFactory.h"
#include "TesInstance.h"
#include "Blueprints/TesBlueprint.h"
#include "Graph/TesBlueprintGraph.h"
#include "Graph/Schema/TesBlueprintGraphSchema_K2.h"

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

	CreateGraphsForNewBlueprint(NewTesAssetBP);

	return NewTesAssetBP;
}

UObject* UTesBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

void UTesBlueprintFactory::CreateGraphsForNewBlueprint(UTesBlueprint* Blueprint)
{
	// �n���ꂽ�u���[�v�����g�ɂ��łɁuGN_EventGraph�v�Ɩ��t����ꂽ�O���t�����݂��邩�`�F�b�N����.
	// GN_EventGraph:Event Graph��\�����ʂȖ��O.
	UEdGraph* EventGraph = FindObject<UEdGraph>(Blueprint, *(UEdGraphSchema_K2::GN_EventGraph.ToString()));

	// ���݂���.
	if (!EventGraph)
	{
		// ���Ƃ��Ƃ�����Event Graph���폜.
#if WITH_EDITORONLY_DATA
		if (Blueprint->UbergraphPages.Num())
		{
			FBlueprintEditorUtils::RemoveGraphs(Blueprint, Blueprint->UbergraphPages);
		}
#endif
		// Event Graph���Đ�������.
		EventGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, UEdGraphSchema_K2::GN_EventGraph, UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());

		/*
		* UbergraphPage:�uMy Blueprint�p�l���v�ɕ\�������Event Graphs�̂���.���ׂẴC�x���g�������܂܂��.
		* �u���[�v�����g���R���p�C�������ƁAUbergraphPage�̂��ׂẴO���t�͑傫�ȃO���t�ɃR�s�[���������ꏈ�������.
		*/
		FBlueprintEditorUtils::AddUbergraphPage(Blueprint, EventGraph);
		// Event Graph�͍폜�s��.
		EventGraph->bAllowDeletion = false;

		// �f�t�H���g�m�[�h�𐶐�.
		const UEdGraphSchema* EventGraphSchema = EventGraph->GetSchema();
		EventGraphSchema->CreateDefaultNodesForGraph(*EventGraph);
	}

	// �ŏ�ʑw�̃f�t�H���g�X�e�[�g�}�V���O���t�𐶐�.
	UTesBlueprintGraph* NewTopLevelGraph = CastChecked<UTesBlueprintGraph>(
		FBlueprintEditorUtils::CreateNewGraph(
		Blueprint,
		UTesBlueprintGraphSchema_K2::GN_TesBlueprintDefinitionGraph,
		UTesBlueprintGraph::StaticClass(),
		UTesBlueprintGraphSchema_K2::StaticClass()
		)
		);
	// �폜�s��.
	NewTopLevelGraph->bAllowDeletion = false;
	// Ubergraph�Ƃ��Ēǉ�.
	FBlueprintEditorUtils::AddUbergraphPage(Blueprint, NewTopLevelGraph);

	// �f�t�H���g�m�[�h�𐶐�
	const UEdGraphSchema* StateMachineGraphSchema = NewTopLevelGraph->GetSchema();
	StateMachineGraphSchema->CreateDefaultNodesForGraph(*NewTopLevelGraph);

	Blueprint->LastEditedDocuments.Reset();
	// �Ō�ɕҏW�����h�L�������g�Ƃ��Đ�������2�̃O���t���w��.
	// ����ŃA�Z�b�g�I�[�v������2�̃O���t���J���ꂽ��ԂɂȂ�.
	Blueprint->LastEditedDocuments.Add(EventGraph);
	Blueprint->LastEditedDocuments.Add(NewTopLevelGraph);
}


#undef LOCTEXT_NAMESPACE
