// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankPlayerController2.h"



void ATankPlayerController2::BeginPlay()
{
	Super::BeginPlay();

	ATank* currentTank = GetControlledTank();
	if (currentTank) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player Controlled tank missing!"));
	}
}

void ATankPlayerController2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrossHair();
}

void ATankPlayerController2::AimAtCrossHair()
{

}

ATank * ATankPlayerController2::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

