// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovement.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovement : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	 void IntendMoveFoward(float Throw);

};
