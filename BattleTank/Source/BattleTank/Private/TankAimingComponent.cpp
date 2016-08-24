// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../Public/TankAimingComponent.h"


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

	// Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity( // Calculate the OutLaunchVelocity
		this,
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Firing at %s"), *AimDirection.ToString())
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			StartLocation + OutLaunchVelocity * 100,
			FColor(255, 0, 0),
			false
		);
	}
	// If no solution found do nothing
	
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * Barrel)
{
	BarrelReference = Barrel;
}
