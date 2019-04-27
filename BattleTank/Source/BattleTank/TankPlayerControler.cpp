// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControler.h"

ATank* ATankPlayerControler::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerControler::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add tank which name is : %s"), *(ControlledTank->GetName()));
	}
}
