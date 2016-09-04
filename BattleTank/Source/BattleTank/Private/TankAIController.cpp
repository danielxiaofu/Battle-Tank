// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/Tank.h"
#include "../Public/TankAIController.h"

void  ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank) {
		// TODO move towards player

		// Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire(); //TODO do not fire in every frame
	}
	
}

