// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovement.generated.h"

class UTankTrack;

/**
 * The class responsible for the movement of the tank
 */

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovement : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	 void IntendMoveFoward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	 void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	 void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);


	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)override;

private:
	UTankTrack* LeftTrack  = nullptr;
	UTankTrack* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float Speed = 40000000.f;
};
