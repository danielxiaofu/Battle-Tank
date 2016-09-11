// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle) 
{
	// Clamp actual throttle value so player cant over drive
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.5, 1.5);
}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit) 
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
	//UE_LOG(LogTemp, Warning, TEXT("%s reporting hit"), *GetName())

}

void UTankTrack::ApplySidewaysForce() {
	// Calculate the slippage speed
	auto TankSpeed = GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(TankSpeed, GetRightVector());
	//UE_LOG(LogTemp, Warning, TEXT("SlippageSpeed = %f"), SlippageSpeed);

	// Work out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways for (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}


