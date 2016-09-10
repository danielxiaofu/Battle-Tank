// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	// Calculate the slippage speed
	auto TankSpeed = GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(TankSpeed, GetRightVector());
	//UE_LOG(LogTemp, Warning, TEXT("SlippageSpeed = %f"), SlippageSpeed);

	// Work out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways for (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) 
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle : %f"), *Name, Throttle);

	// Clamp actual throttle value so player cant over drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return;
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("%s reporting hit"), *GetName())
}


