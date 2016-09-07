// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController2.generated.h"


class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController2 : public APlayerController
{
	GENERATED_BODY()


protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:

	UTankAimingComponent* AimingComponent;

UPROPERTY(EditDefaultsOnly)
float CrossHairXLocation = 0.5f;

UPROPERTY(EditDefaultsOnly)
float CrossHairYLocation = 0.33333f;

UPROPERTY(EditDefaultsOnly)
float LineTraceRange = 1000000.0f;



virtual void BeginPlay() override;

virtual void Tick(float) override;

void AimAtCrossHair();

bool GetSightRayHitLocation(FVector& HitLocation) const;

bool GetLookDirection(FVector2D ScreenLocation, FVector & WorldDirection) const;

bool GetLookVectorHitLocation(const FVector& WorldDirection, FVector& HitLocation) const;
};
