// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::Tick(float FrameTime)
{
	Super::Tick(FrameTime);

	ATank* controlled_tank = Cast<ATank>(GetPawn());
	ATank* player_tank     = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (controlled_tank && player_tank)
	{
		controlled_tank->AimAt(player_tank->GetActorLocation());
		controlled_tank->Fire();
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}
