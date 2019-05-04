 // Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);

	float RotationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	float RawRotation    = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawRotation, 0));
}