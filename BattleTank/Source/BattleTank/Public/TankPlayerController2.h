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

public:
ATank* GetControlledTank() const;
	
virtual void BeginPlay() override;
	
virtual void Tick(float) override;

private:
void AimAtCrossHair();

};
