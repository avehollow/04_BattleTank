// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories =("Collision","Physics") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float DegreesPerSec);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	 float MaxDegreesPerSec = 20.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	 float MinElevateDegrees = 0.0f;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	 float MaxElevateDegrees = 30.0f;
};
