// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;
	virtual void Tick(float FrameTime)override;
	virtual void SetPawn(APawn* Pawn)override;

	UFUNCTION()
	 void OnTankDeath();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	 float AcceptanceRadius = 5000.0f; //50m

};
