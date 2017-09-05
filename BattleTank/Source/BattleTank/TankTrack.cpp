// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	
	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;

	UE_LOG(LogTemp, Warning, TEXT("apply force %s"), *ForceApplied.ToString());

	auto ForceLoaction = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLoaction);
}



