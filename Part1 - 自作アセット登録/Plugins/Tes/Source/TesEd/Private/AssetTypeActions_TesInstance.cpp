// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeActions_TesInstance.h"
#include "Blueprints/TesBlueprint.h"
#include "TesBlueprintFactory.h"

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
