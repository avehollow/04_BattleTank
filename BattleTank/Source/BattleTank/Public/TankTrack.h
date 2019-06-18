

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	 void SetThrottle(float Throttle);

public:
	UPROPERTY(EditDefaultsOnly)
	 float TrackMaxDrivingForce = 40000000.0f;

	float CurrentThrottle = 0;

private:
	UTankTrack();
	virtual void BeginPlay() override;

	void ApplySidewaysForce(float DeltaTime);
	void DriveTrack();

	UFUNCTION()
	 void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
