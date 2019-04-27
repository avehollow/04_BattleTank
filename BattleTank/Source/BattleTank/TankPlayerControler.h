// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerControler.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerControler : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank()const;
	
	virtual void BeginPlay()override;
};
