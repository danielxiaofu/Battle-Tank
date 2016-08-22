// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankPlayerController2.h"



void ATankPlayerController2::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player controller 2 begin play!"));

	ATank* currentTank = GetControlledTank();
	if (currentTank) {
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank %s found!"), *(currentTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Controlled tank missing!"));
	}
}

ATank * ATankPlayerController2::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
