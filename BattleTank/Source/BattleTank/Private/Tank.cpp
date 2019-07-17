// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DMG           = FMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DMG, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
		UE_LOG(LogTemp, Warning, TEXT("Tank Die"))

	return DamageToApply;
}


