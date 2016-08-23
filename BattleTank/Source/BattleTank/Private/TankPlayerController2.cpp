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
	if (!GetControlledTank()) {	return;	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {

	}
	return;
}

ATank * ATankPlayerController2::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController2::GetSightRayHitLocation(FVector& HitLocation) const {
	/// Find the location of the reticle on screen coord
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);


	return false;
}

