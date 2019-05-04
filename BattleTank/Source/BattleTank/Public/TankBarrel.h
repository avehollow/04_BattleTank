// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//UCLASS(meta = (BlueprintSpawnableComponent), hidecategories =("Collision","Physics") )

UCLASS(meta = (BlueprintSpawnableComponent)) //, hidecategories = ("Collision") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	 float MaxDegreesPerSec = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	 float MinElevateDegrees = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	 float MaxElevateDegrees = 30.0f;
};
