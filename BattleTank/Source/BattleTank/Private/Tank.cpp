// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankMovementComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/Projectile.h"
#include "../Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void ATank::AimAt(FVector AimLocation) {
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}


void ATank::Fire()
{
	bool Reloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTime;
	if (!TankAimingComponent) { return; }
	Barrel = TankAimingComponent->BarrelReference;
	if (Barrel && Reloaded) {
		// Spawn a projectile at socket location 
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

	
}

void ATank::SetAimingComponent(UTankAimingComponent* AimingComponent)
{
	TankAimingComponent = AimingComponent;
}


