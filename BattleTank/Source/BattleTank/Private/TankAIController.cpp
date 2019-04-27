// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"


ATank* ATankAIController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Add tank which name is : %s"), *(ControlledTank->GetName()));
	}
}
