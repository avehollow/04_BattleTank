// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimtAt(FVector AimLocation, float Speed)
{
	if (!Barrel) return;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorsToIgnore;

	bool bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(
																this,
																OUT OutLaunchVelocity,
																StartLocation,
																AimLocation,
																Speed,
																false,
																0,
																0,
																ESuggestProjVelocityTraceOption::DoNotTrace,
																FCollisionResponseParams::DefaultResponseParam,
																ActorsToIgnore,
																true
															 );
	if (bHaveSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		this->MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator    = AimDirection.Rotation();
	FRotator DeltaRotator  = AimRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("Aim at: %s"), *(DeltaRotator.ToString()));

	Barrel->Elevate(5);
}

