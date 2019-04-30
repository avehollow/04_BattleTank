// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControler.h"
#include "Engine/World.h"

void ATankPlayerControler::Tick(float FrameTime)
{
	Super::Tick(FrameTime);

	FVector HitLocation;
	if (this->GetSightRayHitLocation(OUT HitLocation))
	{
		this->GetControlledTank()->AimAt(HitLocation);
	}

}

ATank* ATankPlayerControler::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerControler::AimTowardsCrosshair()
{
	if (!this->GetControlledTank()) return;


}

bool ATankPlayerControler::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector WorldLookDirection;
	if (this->GetLookDirection(ScreenLocation, OUT WorldLookDirection))
	{
		if (this->GetVectorHitLocation(WorldLookDirection, OUT OutHitLocation))
			return true;
	}
	return false;
}

bool ATankPlayerControler::GetLookDirection(FVector2D ScreenLocation, FVector & WorldLookDirection) const
{
	FVector WorldCameraLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT WorldCameraLocation, OUT WorldLookDirection);
}

bool ATankPlayerControler::GetVectorHitLocation(FVector WorldDirection, FVector& HitLocation)const
{
	FHitResult HitResult;
	
	FVector StartTrace = PlayerCameraManager->GetCameraLocation();
	FVector EndTrace   = StartTrace + (WorldDirection * LinetraceRage);
	
	bool IsHit = GetWorld()->LineTraceSingleByChannel(
															OUT HitResult,
															StartTrace,
															EndTrace,
															ECollisionChannel(ECC_Visibility)
													 );
	if (IsHit)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}

void ATankPlayerControler::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add tank which name is : %s"), *(ControlledTank->GetName()));
	}
}
