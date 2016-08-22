// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankPlayerController2.h"



void ATankPlayerController2::BeginPlay()
{
	Super::BeginPlay();

	ATank* currentTank = GetControlledTank();
	if (currentTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controlled tank %s found!"), *(currentTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player Controlled tank missing!"));
	}
}

ATank * ATankPlayerController2::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
