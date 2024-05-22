// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerController.h"
#include "SFR_PlayerCamera.h"
#include "Kismet/GameplayStatics.h"

void ASFR_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Spawn the custom Camera
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    CameraActor = GetWorld()->SpawnActor<ASFR_PlayerCamera>(
        ASFR_PlayerCamera::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

    if (CameraActor)
    {
        // Set the Camera to follow the player
        AActor* PlayerPawn = GetPawn();
        if (PlayerPawn)
        {
            CameraActor->SetFollowTarget(PlayerPawn);
        }

        // Optionally, set the view target to the main camera
        SetViewTarget(CameraActor);

    }

}

//void ASFR_PlayerController::SetupInputComponent()
//{
//    Super::SetupInputComponent();
//
//
//}