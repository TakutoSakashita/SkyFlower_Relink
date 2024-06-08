// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_PlayerController.h"
#include "SFA_Camera.h"

void ASFA_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the custom Camera
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (!CameraClass) {
		CameraClass = ASFA_Camera::StaticClass();
	}
	Camera = GetWorld()->SpawnActor<ASFA_Camera>(CameraClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);



	if (Camera) {
		// Set the Camera to follow the player
		AActor* PlayerPawn = GetPawn();
		if (PlayerPawn){
			Camera->SetFollowTarget(PlayerPawn);
		}

		// Optionally, set the view target to the main camera
		SetViewTarget(Camera);
	}
}
