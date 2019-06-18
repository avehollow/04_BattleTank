// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Reloading,
	Locked
};



class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector AimLocation);
	EFiringStatus GetFiringStatus() const;
	
	UFUNCTION(BlueprintCallable, Category = "Fire")
	 void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	 void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

public:
	UPROPERTY(BlueprintReadOnly, Category = Firing)
	 int ammunition = 10;

protected:
	UPROPERTY(BlueprintReadOnly)
	 EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	virtual void BeginPlay() override;

	// When body of this function is in cpp file i get error "Tick Component not found"
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override
	{
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSec) 
		{
			FiringStatus = EFiringStatus::Reloading;
		}
		else if(IsBarrelMoving())
		{
			FiringStatus = EFiringStatus::Aiming;
		}
		else
		{
			FiringStatus = EFiringStatus::Locked;
		}
	}



	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	bool IsBarrelMoving();

private:
	UTankBarrel* Barrel = nullptr; 
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	 float LunchSpeed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	 TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	 float ReloadTimeInSec = 3.0f;

	double LastFireTime = 0.0;

	FVector AimDirection = FVector::ZeroVector;
};
