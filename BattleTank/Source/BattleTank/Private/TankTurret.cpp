// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Traverse(float RelativeSpeed) {
	auto YawChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreePerSecond * GetWorld()->GetDeltaSeconds();
	auto Traverse = RelativeRotation.Yaw + YawChange;
	SetRelativeRotation(FRotator(0, Traverse, 0));
}


