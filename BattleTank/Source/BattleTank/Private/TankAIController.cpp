// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void  ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* currentTank = GetControlledTank();
	if (currentTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled tank %s found!"), *(currentTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI Controlled tank missing!"));
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

