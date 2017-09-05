// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration
class UTankAimingComponent;
class UTankTurrent;
class UTankBarrel;
class UTankTrack;
class AProjectile;
//Hold barrel's property and elevation method

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;


public:	

	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurrentReference(UTankTurrent* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; 

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

private:
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
