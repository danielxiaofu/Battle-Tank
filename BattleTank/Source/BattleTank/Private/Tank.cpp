// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/Projectile.h"
#include "../Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector AimLocation) {
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelReference)
{
	TankAimingComponent->SetBarrelReference(BarrelReference);
	Barrel = BarrelReference;
}

void ATank::SetTurretReference(UTankTurret * TurretReference)
{
	TankAimingComponent->SetTurretReference(TurretReference);
}

void ATank::Fire()
{
	bool Reloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTime;
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


