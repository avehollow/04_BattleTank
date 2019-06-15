// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/Projectile.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"

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

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel)) return;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorsToIgnore;
	//ActorsToIgnore.Add(GetOwner());

	bool bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(
																this,
																OUT OutLaunchVelocity,
																StartLocation,
																AimLocation,
																LunchSpeed,
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		this->MoveTurretTowards(AimDirection);
		this->MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (Barrel && 
	    ProjectileBlueprint &&
		FiringStatus != EFiringStatus::Reloading)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));

		Projectile->LaunchProjectile(LunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		FiringStatus = EFiringStatus::Reloading;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) return;
	UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::Initialize"));
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator    = AimDirection.Rotation();
	FRotator DeltaRotator  = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator    = AimDirection.Rotation();
	FRotator DeltaRotator  = AimRotator - BarrelRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!Barrel) return false;
	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.1));
}

