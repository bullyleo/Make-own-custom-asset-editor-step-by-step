// Fill out your copyright notice in the Description page of Project Settings.


#include "TesBlueprintEditorModes.h"
#include "TesBlueprintEditor.h"

#include "BlueprintEditorTabs.h"
#include "SBlueprintEditorToolbar.h"


const FName FTesEditorModes::TesEditorName("TesEditorApp");
const FName FTesEditorModes::TesBlueprintMode("GraphName");

FTesBlueprintEditorMode::FTesBlueprintEditorMode(TSharedPtr<class FTesBlueprintEditor> EditorIn)
	: FBlueprintEditorApplicationMode(StaticCastSharedPtr<FBlueprintEditor>(EditorIn), 
									  FTesEditorModes::TesBlueprintMode, 
									  FTesEditorModes::GetLocalizedMode, 
									  false, 
									  false)
{
	// エディタレイアウトを定義.(ここの名前でレイアウトが保存される)
	TabLayout = FTabManager::NewLayout("TesBlueprintEditMode_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			// 上下に分割.
			->SetOrientation(Orient_Vertical)
			->Split
			(
				// 上部のツールバー.(コンパイルボタンとかプレイボタンがあるエリア)
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->SetHideTabWell(true)
				->AddTab(EditorIn->GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				// メインアプリケーションエリア.
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					// 左側.
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					// MyBlueprintパネル(Graphs & Variables)
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(1.f)
						->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab)
						->SetForegroundTab(FBlueprintEditorTabs::MyBlueprintID)
					)
				)
				->Split
				(
					// 真ん中.
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.6f)
					->Split
					(
						// 中上 - グラフエリア
						FTabManager::NewStack()
						->SetSizeCoefficient(0.8f)
						->AddTab("Document", ETabState::ClosedTab)
					)
					->Split
					(
						// 中下 - compiler results & find
						FTabManager::NewStack()
						->SetSizeCoefficient(0.2f)
						->AddTab(FBlueprintEditorTabs::CompilerResultsID, ETabState::ClosedTab)
						->AddTab(FBlueprintEditorTabs::FindResultsID, ETabState::ClosedTab)
					)
				)
				->Split
				(
					// 右側
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						// Detailsパネル
						FTabManager::NewStack()
						->SetSizeCoefficient(1.f)
						->AddTab(FBlueprintEditorTabs::DetailsID, ETabState::OpenedTab)
					)
				)
			)
		);

	ToolbarExtender = MakeShareable(new FExtender);

	if (UToolMenu* Toolbar = EditorIn->RegisterModeToolbarIfUnregistered(GetModeName()))
	{
		// コンパイルボタン.
		EditorIn->GetToolbarBuilder()->AddCompileToolbar(Toolbar);
		// Find、UnrelatedNodesOptionsとか.
		EditorIn->GetToolbarBuilder()->AddScriptingToolbar(Toolbar);
		// Class Settings、Class Defaultsとか.
		EditorIn->GetToolbarBuilder()->AddBlueprintGlobalOptionsToolbar(Toolbar);
		// Debug Filterドロップダウンメニューとか.
		EditorIn->GetToolbarBuilder()->AddDebuggingToolbar(Toolbar);
	}
}
