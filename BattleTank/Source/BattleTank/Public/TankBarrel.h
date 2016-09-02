// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreePerSecond = 20; // Sensible defaults

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;

	void Elevate(float DegreesPerSecond);
	
	
};
