// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeActions_TesInstance.h"
#include "Blueprints/TesBlueprint.h"
#include "TesBlueprintFactory.h"
#include "TesBlueprintEditor.h"

////////////////////////////////////////////////////////////////////
// FAssetTypeActions_TesBase

FAssetTypeActions_TesBase::FAssetTypeActions_TesBase(uint32 Categories)
    : MyAssetCategory(Categories)
{}


////////////////////////////////////////////////////////////////////
// FAssetTypeActions_TesBlueprint

FAssetTypeActions_TesBlueprint::FAssetTypeActions_TesBlueprint(uint32 InAssetCategory)
    : FAssetTypeActions_TesBase(InAssetCategory)
{}

UClass* FAssetTypeActions_TesBlueprint::GetSupportedClass() const
{
    return UTesBlueprint::StaticClass();
}


void FAssetTypeActions_TesBlueprint::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	// Content Browserで選択中のアセットに対して...
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		// UTesBlueprintアセットであることをチェック.
		if (UTesBlueprint* TesBP = Cast<UTesBlueprint>(*ObjIt))
		{
			// エディタインスタンスを作成＆初期化.
			TSharedRef<FTesBlueprintEditor> BlueprintEditor(new FTesBlueprintEditor());
			BlueprintEditor->InitTesBlueprintEditor(Mode, EditWithinLevelEditor, TesBP);
		}
	}
}
