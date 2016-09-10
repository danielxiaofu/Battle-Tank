// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAimingComponent.h"
#include"../Public/TankBarrel.h"
#include"../Public/TankTurret.h"
#include "../Public/Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}


}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	/// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if (!ensure(TurretToSet && BarrelToSet)) { return; }
	TurretReference = TurretToSet;
	BarrelReference = BarrelToSet;
}

void  UTankAimingComponent::AimAt(FVector AimLocation) {
	if (!ensure(BarrelReference)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = BarrelReference->GetSocketLocation(FName("Projectile"));
	FCollisionResponseParams CollisionRes;

	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	( // Calculate the OutLaunchVelocity
		this,
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//,CollisionRes,
		//TArray<AActor*>(),
		//true
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : No aim solve found"), Time);
	}
	
	/*DrawDebugLine(
		GetWorld(),
		StartLocation,
		StartLocation + OutLaunchVelocity,
		FColor::Red,
		false,
		-1,
		'\000',
		10
	);*/

}

void UTankAimingComponent::Fire()
{
	
	if (!ensure(BarrelReference)) { return; }
	if (!(FiringStatus == EFiringStatus::Reloading)) {
		// Spawn a projectile at socket location 
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			BarrelReference->GetSocketLocation(FName("Projectile")),
			BarrelReference->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// Work out difference between current barrel rotation and AimDirection
	if (!ensure(BarrelReference)) { return; }
	auto BarrelRotator = BarrelReference->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	BarrelReference->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(TurretReference)) { return; }
	auto TurretRotator = TurretReference->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - TurretRotator;

	TurretReference->Traverse(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(BarrelReference)) { return false; }
	return !BarrelReference->GetForwardVector().GetSafeNormal().Equals(AimDirection, 0.01f);
}
