// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovement;
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector AimLocation);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	 void SetBarrel(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	 void SetTurret(UTankTurret* TurretToSet);
	
	UFUNCTION(BlueprintCallable, Category = Mechanisms)
	 void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UTankAimingComponent*         AimingComponent			 = nullptr;

	UPROPERTY(BlueprintReadOnly)
	 UTankMovement*				  MovementComponent			 = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	 TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	 float LunchSpeed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	 float ReloadTimeInSec = 3.0f;

	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0.0;
};
