// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAimingComponent.h"
#include"../Public/TankBarrel.h"
#include"../Public/TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void  UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed) {
	if (!BarrelReference) { return;  }

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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : No aim solve found"), Time);
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

void UTankAimingComponent::SetBarrelReference(UTankBarrel * Barrel)
{
	if (!Barrel) { return; }
	BarrelReference = Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * Turret)
{
	if (!Turret) { return; }
	TurretReference = Turret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = BarrelReference->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	BarrelReference->Elevate(DeltaRotator.Pitch); // TODO Make a variable
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = TurretReference->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - TurretRotator;

	TurretReference->Traverse(DeltaRotator.Yaw);
}
