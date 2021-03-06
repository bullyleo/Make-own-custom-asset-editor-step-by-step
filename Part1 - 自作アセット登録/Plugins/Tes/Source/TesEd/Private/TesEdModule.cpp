	// Copyright Epic Games, Inc. All Rights Reserved.

#include "TesEdModule.h"
#include "AssetTypeActions_TesInstance.h"
#include "Blueprints/TesBlueprint.h"

#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FTesEdModule"

void FTesEdModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// 自作のアセットカテゴリを登録する
	const EAssetTypeCategories::Type AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Tes")), LOCTEXT("TesAssetCategory", "Tes User Defined"));

	// 自作AssetTypeActionを登録.
	TSharedRef<IAssetTypeActions> TesBlueprintAssetAction = MakeShareable(new FAssetTypeActions_TesBlueprint(EAssetTypeCategories::Blueprint | AssetCategoryBit));
	AssetTools.RegisterAssetTypeActions(TesBlueprintAssetAction);

	CreatedAssetTypeActions.Add(TesBlueprintAssetAction);
}

void FTesEdModule::ShutdownModule()
{
	// 登録したAssetTypeActionをすべて解除する.
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTesEdModule, TesEd)