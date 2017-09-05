// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurrent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurrentReference(UTankTurrent* TurrentToSet) {
	Turrent = TurrentToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	
	//if no barrel
	if (!Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLcoation = Barrel->GetSocketLocation(FName("Head"));
	auto TankName = GetOwner()->GetName();

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLcoation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)//calculate projectile
	{
		//print rersult
		//calculate outLaunch velocity direction
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"),*TankName, *AimDirection.ToString());

		//move barrel to aim at 
		MoveBarrel(AimDirection);

		return;
	}

	//did not find 
	UE_LOG(LogTemp, Warning, TEXT("%s No aim found"),*TankName);
	
}

void UTankAimingComponent::MoveBarrel(FVector AimDorection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDorection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	
	//move the barrel 
	Barrel->Elevate(DeltaRotator.Pitch);



	//give a max elevatin speed
}
