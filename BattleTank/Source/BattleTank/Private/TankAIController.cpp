// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::Tick(float FrameTime)
{
	Super::Tick(FrameTime);

	ATank* controlled_tank = this->GetControlledTank();
	ATank* player_tank     = this->GetPlayerTank();
	
	if(controlled_tank && player_tank)
		controlled_tank->AimAt(player_tank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Add tank which name is : %s"), *(ControlledTank->GetName()));
	}

	ATank* player_tank = this->GetPlayerTank();
	if (player_tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank found %s"), *(player_tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank not found"));
	}
}
