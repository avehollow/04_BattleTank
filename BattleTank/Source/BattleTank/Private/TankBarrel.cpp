// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);

	float ElevationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	float RawElevation = RelativeRotation.Pitch + ElevationChange;

	RawElevation = FMath::Clamp(RawElevation, MinElevateDegrees, MaxElevateDegrees);
	SetRelativeRotation(FRotator(RawElevation, 0, 0));
}