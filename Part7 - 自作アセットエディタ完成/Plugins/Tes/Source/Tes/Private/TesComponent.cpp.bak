// Fill out your copyright notice in the Description page of Project Settings.


#include "TesComponent.h"
#include "TesInstance.h"

// Sets default values for this component's properties
UTesComponent::UTesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTesComponent::RunTesInstance(TSubclassOf<UTesInstance> TesBlueprintClass)
{
	if (!TesInstance)
	{
		TesInstance = NewObject<UTesInstance>(GetOwner(), TesBlueprintClass, NAME_None, RF_NoFlags, nullptr);
		TesInstance->Initialize(GetOwner());
	}

	TesInstance->Start();
}