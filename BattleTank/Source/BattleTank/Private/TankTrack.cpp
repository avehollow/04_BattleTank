// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() 
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce(float DeltaTime)
{
	// dotProduct = cos a betweem this two vectors
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CorrectionAcceleration = -SlippageSpeed * DeltaTime * GetRightVector();

	auto  TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector Force = (CorrectionAcceleration * TankRoot->GetMass()) / 2; // Divide by 2 because is 2 track
	TankRoot->AddForce(Force);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit! Sir !!!"));
	this->DriveTrack();
	this->ApplySidewaysForce(GetWorld()->GetDeltaSeconds());
	// Without it, tank will keep moving forever
	CurrentThrottle = 0;
}



void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}