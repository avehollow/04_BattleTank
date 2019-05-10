// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankMovement.h"
#include "../Public/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent   = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector AimLocation)
{
	AimingComponent->AimtAt(AimLocation, LunchSpeed);
}

void ATank::SetBarrel(UTankBarrel * BarrelToSet)
{
	//if (!BarrelToSet) return;
	AimingComponent->SetBarrel(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurret(UTankTurret * TurretToSet)
{
	//if (!TurretToSet) return;
	AimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire()
{
	bool IsReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSec;
	
	if (Barrel && IsReload)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

