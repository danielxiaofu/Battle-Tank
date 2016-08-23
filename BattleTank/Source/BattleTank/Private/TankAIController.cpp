// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAIController.h"

void  ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* currentTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();
	if (currentTank) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI Controlled tank missing!"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

