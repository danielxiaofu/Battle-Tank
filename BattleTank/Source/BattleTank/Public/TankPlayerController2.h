// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController2.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController2 : public APlayerController
{
	GENERATED_BODY()



private:

UPROPERTY(EditAnyWhere)
float CrossHairXLocation = 0.5f;

UPROPERTY(EditAnyWhere)
float CrossHairYLocation = 0.33333f;

ATank* GetControlledTank() const;

virtual void BeginPlay() override;

virtual void Tick(float) override;

void AimAtCrossHair();

bool GetSightRayHitLocation(FVector& HitLocation) const;
};
