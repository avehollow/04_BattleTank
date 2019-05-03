 // Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);

	float ElevationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	float RawElevation    = RelativeRotation.Yaw + ElevationChange;

	SetRelativeRotation(FRotator(0, RawElevation, 0));
}