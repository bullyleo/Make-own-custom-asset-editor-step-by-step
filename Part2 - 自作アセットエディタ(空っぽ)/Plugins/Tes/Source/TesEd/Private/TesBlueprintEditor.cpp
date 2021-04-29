// Fill out your copyright notice in the Description page of Project Settings.


#include "TesBlueprintEditor.h"
#include "Blueprints/TesBlueprint.h"

#include "SBlueprintEditorToolbar.h"
#include "Kismet2/DebuggerCommands.h"


void FTesBlueprintEditor::InitTesBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UTesBlueprint* Blueprint)
{
	// 「このブループリントはすでに何かしらのエディタで開かれた」とマークする.
	Blueprint->bIsNewlyCreated = false;

	if (!Toolbar.IsValid())
	{
		Toolbar = MakeShareable(new FBlueprintEditorToolbar(SharedThis(this)));
	}

	// So the play bar matches the level bar.
	GetToolkitCommands()->Append(FPlayWorldCommands::GlobalPlayWorldActions.ToSharedRef());

	// エディタの基本的なコマンドを登録.
	CreateDefaultCommands();
	// 基本的なメニューバーの内容を登録.
	RegisterMenus();

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	// エディタの初期化.
	InitAssetEditor(Mode, InitToolkitHost, TEXT("TesEditorApp"), FTabManager::FLayout::NullLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, Blueprint);

	TArray<UBlueprint*> Blueprints;
	Blueprints.Add(Blueprint);

	// ブループリントの初期化
	CommonInitialization(Blueprints, false);

	// メニューバー、ツールバーを再生成.
	RegenerateMenusAndToolbars();

	PostLayoutBlueprintEditorInitialization();
}
