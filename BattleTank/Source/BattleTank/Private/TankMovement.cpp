// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovement.h"
#include "../Public/TankTrack.h"

void UTankMovement::IntendMoveFoward(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovement::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovement::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (LeftTrackToSet && RightTrackToSet)
	{
		LeftTrack  = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}

void UTankMovement::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForward   = MoveVelocity.GetSafeNormal();

	UE_LOG(LogTemp, Warning, TEXT("%s MoveVelocity"), *(GetOwner()->GetName()));

	float dot = FVector::DotProduct(TankForward, AIForward);
	this->IntendMoveFoward(dot);
}
