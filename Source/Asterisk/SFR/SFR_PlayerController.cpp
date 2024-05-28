// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerController.h"
#include "SFR_Camera.h"

void ASFR_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Spawn the custom Camera
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    Camera = GetWorld()->SpawnActor<ASFR_Camera>(
        ASFR_Camera::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

    if (Camera)
    {
        // Set the Camera to follow the player
        AActor* PlayerPawn = GetPawn();
        if (PlayerPawn)
        {
            Camera->SetFollowTarget(PlayerPawn);
        }

        // Optionally, set the view target to the main camera
        SetViewTarget(Camera);

    }
}
