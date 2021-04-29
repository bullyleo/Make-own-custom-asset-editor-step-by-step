// Fill out your copyright notice in the Description page of Project Settings.


#include "TesBlueprintEditor.h"
#include "Blueprints/TesBlueprint.h"

#include "SBlueprintEditorToolbar.h"
#include "Kismet2/DebuggerCommands.h"


void FTesBlueprintEditor::InitTesBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UTesBlueprint* Blueprint)
{
	// �u���̃u���[�v�����g�͂��łɉ�������̃G�f�B�^�ŊJ���ꂽ�v�ƃ}�[�N����.
	Blueprint->bIsNewlyCreated = false;

	if (!Toolbar.IsValid())
	{
		Toolbar = MakeShareable(new FBlueprintEditorToolbar(SharedThis(this)));
	}

	// So the play bar matches the level bar.
	GetToolkitCommands()->Append(FPlayWorldCommands::GlobalPlayWorldActions.ToSharedRef());

	// �G�f�B�^�̊�{�I�ȃR�}���h��o�^.
	CreateDefaultCommands();
	// ��{�I�ȃ��j���[�o�[�̓��e��o�^.
	RegisterMenus();

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	// �G�f�B�^�̏�����.
	InitAssetEditor(Mode, InitToolkitHost, TEXT("TesEditorApp"), FTabManager::FLayout::NullLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, Blueprint);

	TArray<UBlueprint*> Blueprints;
	Blueprints.Add(Blueprint);

	// �u���[�v�����g�̏�����
	CommonInitialization(Blueprints, false);

	// ���j���[�o�[�A�c�[���o�[���Đ���.
	RegenerateMenusAndToolbars();

	PostLayoutBlueprintEditorInitialization();
}
