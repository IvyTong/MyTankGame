// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlTank = GetControlledTank();
	if (!ControlTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possess"));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Possess %s"),*ControlTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossair()
{
	if (!GetControlledTank()) 
	{ 
		return;
	}

	FVector HitLocation;//out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//print out hit location
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		//tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	
	
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) 
{
	if(GetLookVectorHitLocation(HitLocation))
	{

		//tell the tank to aim at the hit location
		GetControlledTank()->AimAt(HitLocation);
		return true;
	}


	//return OUT parameter HitLocation
	return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation)
{

	//get look direction
	 FVector LookDirection;
	 //find crosshair screen position
	 int32 ViewportSizeX, ViewportSizeY;
	 GetViewportSize(ViewportSizeX, ViewportSizeY);
	 auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	 //UE_LOG(LogTemp, Warning, TEXT("screen location: %s"), *ScreenLocation.ToString());


	 //line trace look direction to find world location
	 if (GetLookDirection(ScreenLocation, LookDirection))
	 {
		 FHitResult HitResult;
		 auto StartLocation = PlayerCameraManager->GetCameraLocation();
		 auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	 
		//line trace to get hit location
		 if(GetWorld()->LineTraceSingleByChannel(HitResult, 
			 StartLocation, 
			 EndLocation, 
			 ECollisionChannel::ECC_Visibility))
		 { 
			 HitLocation = HitResult.Location;
			 return true;
		 }
	 }

	HitLocation = FVector(1, 1, 1);
	return false;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	//de-project the screen position to a world dirtion
	FVector CameraWorldLocation;//to be discared
	bool result = DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
	
	return result;
}