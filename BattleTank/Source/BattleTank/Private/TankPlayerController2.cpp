// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankPlayerController2.h"



void ATankPlayerController2::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(GetPawn())) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; } 
	FoundAimingComponent(AimingComponent);
	
}

void ATankPlayerController2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrossHair();
}

void ATankPlayerController2::AimAtCrossHair()
{

	if (!ensure(AimingComponent)) {	return;	}
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
	return;
}

bool ATankPlayerController2::GetSightRayHitLocation(FVector& HitLocation) const {

	/// Find the location of the reticle on screen coord
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	/// De-project the screen location to world location and get the look direction
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		/// Line trace alone the look direction
		FVector HitLocation;
		if (GetLookVectorHitLocation(WorldDirection, HitLocation)) {
			AimingComponent->AimAt(HitLocation);
			return true;
		}
	}

	return false;
}

bool ATankPlayerController2::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const {
	/// De-project the screen location to world location
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		WorldDirection);
	
}

bool ATankPlayerController2::GetLookVectorHitLocation(const FVector& WorldDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + WorldDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		/// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}