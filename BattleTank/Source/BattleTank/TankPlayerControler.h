// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerControler.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerControler : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;
	virtual void Tick(float FrameTime)override;

public:
	UPROPERTY(EditAnywhere)
	 float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	 float CrosshairYLocation = 0.33333333f;
	
	UPROPERTY(EditAnywhere)
	 float LinetraceRage = 1000000.0f;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	 void FindAimingComponent(UTankAimingComponent* TankAimingComponent);

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation )const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldLookDirection)const;
	bool GetVectorHitLocation(FVector WorldDirection, FVector& HitLocation)const;
};