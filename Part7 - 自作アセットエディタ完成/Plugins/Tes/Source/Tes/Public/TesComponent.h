// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TesComponent.generated.h"


UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent, DisplayName = "TesComponent"))
class TES_API UTesComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UTesInstance* TesInstance;

public:	
	// Sets default values for this component's properties
	UTesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	UFUNCTION(BlueprintCallable, Category = "Tes")
		void RunTesInstance(TSubclassOf<class UTesInstance> TesBlueprintClass);

	UFUNCTION(BlueprintCallable, Category = "Tes")
		void StopTesInstance();

};
