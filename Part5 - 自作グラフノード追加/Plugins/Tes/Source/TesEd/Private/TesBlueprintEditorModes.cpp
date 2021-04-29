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
	// �G�f�B�^���C�A�E�g���`.(�����̖��O�Ń��C�A�E�g���ۑ������)
	TabLayout = FTabManager::NewLayout("TesBlueprintEditMode_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			// �㉺�ɕ���.
			->SetOrientation(Orient_Vertical)
			->Split
			(
				// �㕔�̃c�[���o�[.(�R���p�C���{�^���Ƃ��v���C�{�^��������G���A)
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->SetHideTabWell(true)
				->AddTab(EditorIn->GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				// ���C���A�v���P�[�V�����G���A.
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					// ����.
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					// MyBlueprint�p�l��(Graphs & Variables)
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(1.f)
						->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab)
						->SetForegroundTab(FBlueprintEditorTabs::MyBlueprintID)
					)
				)
				->Split
				(
					// �^��.
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.6f)
					->Split
					(
						// ���� - �O���t�G���A
						FTabManager::NewStack()
						->SetSizeCoefficient(0.8f)
						->AddTab("Document", ETabState::ClosedTab)
					)
					->Split
					(
						// ���� - compiler results & find
						FTabManager::NewStack()
						->SetSizeCoefficient(0.2f)
						->AddTab(FBlueprintEditorTabs::CompilerResultsID, ETabState::ClosedTab)
						->AddTab(FBlueprintEditorTabs::FindResultsID, ETabState::ClosedTab)
					)
				)
				->Split
				(
					// �E��
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						// Details�p�l��
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
		// �R���p�C���{�^��.
		EditorIn->GetToolbarBuilder()->AddCompileToolbar(Toolbar);
		// Find�AUnrelatedNodesOptions�Ƃ�.
		EditorIn->GetToolbarBuilder()->AddScriptingToolbar(Toolbar);
		// Class Settings�AClass Defaults�Ƃ�.
		EditorIn->GetToolbarBuilder()->AddBlueprintGlobalOptionsToolbar(Toolbar);
		// Debug Filter�h���b�v�_�E�����j���[�Ƃ�.
		EditorIn->GetToolbarBuilder()->AddDebuggingToolbar(Toolbar);
	}
}
