// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControler.h"
#include "Engine/World.h"
#include "../Public/Tank.h"
#include "../Public/TankAimingComponent.h"

void ATankPlayerControler::Tick(float FrameTime)
{
	Super::Tick(FrameTime);

	this->AimTowardsCrosshair();
}

void ATankPlayerControler::SetPawn(APawn * Pawn)
{
	Super::SetPawn(Pawn);

	ATank* tank = Cast<ATank>(Pawn);
	if (!ensure(tank)) return;

	tank->OnDeath.AddUniqueDynamic(this, &ATankPlayerControler::OnTankDeath);
}

void ATankPlayerControler::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerControler::AimTowardsCrosshair()
{
	if (!ensure(GetPawn()))	 return;


	UTankAimingComponent* aiming_component = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!aiming_component) return;

	FVector HitLocation;
	if (this->GetSightRayHitLocation(OUT HitLocation))
	{
		aiming_component->AimAt(HitLocation);
	}
}

bool ATankPlayerControler::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector WorldLookDirection;
	if (this->GetLookDirection(ScreenLocation, OUT WorldLookDirection))
	{
		return this->GetVectorHitLocation(WorldLookDirection, OUT OutHitLocation);
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
    UTankAimingComponent* aiming_component =  GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (aiming_component)
	{
		this->FindAimingComponent(aiming_component);
	}
}
