// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;
class UTankTurret;

// Hold barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* BarrelReference = nullptr;

	UTankTurret* TurretReference = nullptr;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Aim at provided location
	void AimAt(FVector, float);
	
	void SetBarrelReference(UTankBarrel* Barrel);

	void SetTurretReference(UTankTurret* Turret);

private:
	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);
};
