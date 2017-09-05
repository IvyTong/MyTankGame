// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	void AimAt(FVector HitLocation,float LaunchSpeed);
	
	void MoveBarrel(FVector AimDorection);
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UTankBarrel* Barrel = nullptr;

};
