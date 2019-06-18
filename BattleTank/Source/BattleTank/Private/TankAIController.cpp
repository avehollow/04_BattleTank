// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::Tick(float FrameTime)
{
	Super::Tick(FrameTime);

	APawn* controlled_tank = GetPawn();
	APawn* player_tank     = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (controlled_tank && player_tank)
	{
		UTankAimingComponent* aiming_component = controlled_tank->FindComponentByClass<UTankAimingComponent>();
		MoveToActor(player_tank, AcceptanceRadius);
		aiming_component->AimAt(player_tank->GetActorLocation());

		if (aiming_component->GetFiringStatus() == EFiringStatus::Locked)
		{
			aiming_component->Fire();
		}
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}
