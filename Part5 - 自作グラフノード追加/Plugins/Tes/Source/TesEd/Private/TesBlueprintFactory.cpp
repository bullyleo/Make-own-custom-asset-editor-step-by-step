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

	CreateGraphsForNewBlueprint(NewTesAssetBP);

	return NewTesAssetBP;
}

UObject* UTesBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

void UTesBlueprintFactory::CreateGraphsForNewBlueprint(UTesBlueprint* Blueprint)
{
	// 渡されたブループリントにすでに「GN_EventGraph」と名付けられたグラフが存在するかチェックする.
	// GN_EventGraph:Event Graphを表す特別な名前.
	UEdGraph* EventGraph = FindObject<UEdGraph>(Blueprint, *(UEdGraphSchema_K2::GN_EventGraph.ToString()));

	// 存在した.
	if (!EventGraph)
	{
		// もともとあったEvent Graphを削除.
#if WITH_EDITORONLY_DATA
		if (Blueprint->UbergraphPages.Num())
		{
			FBlueprintEditorUtils::RemoveGraphs(Blueprint, Blueprint->UbergraphPages);
		}
#endif
		// Event Graphを再生成する.
		EventGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, UEdGraphSchema_K2::GN_EventGraph, UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());

		/*
		* UbergraphPage:「My Blueprintパネル」に表示されるEvent Graphsのこと.すべてのイベント実装が含まれる.
		* ブループリントがコンパイルされると、UbergraphPageのすべてのグラフは大きなグラフにコピー＆統合され処理される.
		*/
		FBlueprintEditorUtils::AddUbergraphPage(Blueprint, EventGraph);
		// Event Graphは削除不可.
		EventGraph->bAllowDeletion = false;

		// デフォルトノードを生成.
		const UEdGraphSchema* EventGraphSchema = EventGraph->GetSchema();
		EventGraphSchema->CreateDefaultNodesForGraph(*EventGraph);
	}

	// 最上位層のデフォルトステートマシングラフを生成.
	UTesBlueprintGraph* NewTopLevelGraph = CastChecked<UTesBlueprintGraph>(
		FBlueprintEditorUtils::CreateNewGraph(
		Blueprint,
		UTesBlueprintGraphSchema_K2::GN_TesBlueprintDefinitionGraph,
		UTesBlueprintGraph::StaticClass(),
		UTesBlueprintGraphSchema_K2::StaticClass()
		)
		);
	// 削除不可.
	NewTopLevelGraph->bAllowDeletion = false;
	// Ubergraphとして追加.
	FBlueprintEditorUtils::AddUbergraphPage(Blueprint, NewTopLevelGraph);

	// デフォルトノードを生成
	const UEdGraphSchema* StateMachineGraphSchema = NewTopLevelGraph->GetSchema();
	StateMachineGraphSchema->CreateDefaultNodesForGraph(*NewTopLevelGraph);

	Blueprint->LastEditedDocuments.Reset();
	// 最後に編集したドキュメントとして生成した2つのグラフを指定.
	// これでアセットオープン時に2つのグラフが開かれた状態になる.
	Blueprint->LastEditedDocuments.Add(EventGraph);
	Blueprint->LastEditedDocuments.Add(NewTopLevelGraph);
}


#undef LOCTEXT_NAMESPACE
