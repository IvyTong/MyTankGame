// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlTank = GetControlledTank();
	if (!ControlTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController Not Possess"));
	}
	UE_LOG(LogTemp, Warning, TEXT("TankAIController Possess %s"), *ControlTank->GetName());

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController did no find player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player"), *PlayerTank->GetName());
	}

}

ATank*  ATankAIController::GetPlayerTank() const
{
	ATank* PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerPawn) { return nullptr; }

	return PlayerPawn;
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	if (GetPlayerTank())
	{
		//move towards player

		//aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire if in range
	}
}


