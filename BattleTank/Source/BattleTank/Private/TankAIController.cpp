// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAIController.h"

void  ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* currentTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();
	if (currentTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled tank %s found!"), *(currentTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI Controlled tank missing!"));
	}
	if (playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controlled tank %s found by AI %s"), *(playerTank->GetName()), *(currentTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr; }
	return Cast<ATank>(playerPawn);
}

