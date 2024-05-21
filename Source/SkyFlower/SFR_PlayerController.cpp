// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerController.h"
#include "SFR_PlayerCamera.h"
#include "Kismet/GameplayStatics.h"

void ASFR_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Spawn the custom CameraActor
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    CameraActor = GetWorld()->SpawnActor<ASFR_PlayerCamera>(
        ASFR_PlayerCamera::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

    if (CameraActor)
    {
        // Set the CameraActor to follow the player
        AActor* PlayerPawn = GetPawn();
        if (PlayerPawn)
        {
            CameraActor->SetFollowTarget(PlayerPawn);
        }

        // Optionally, set the view target to the main camera
        SetViewTarget(CameraActor);

    }

}

void ASFR_PlayerController::Turn(float Rate)
{
    AddYawInput(Rate);
}

void ASFR_PlayerController::LookUp(float Rate)
{
    AddPitchInput(Rate);
}

void ASFR_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("Turn", this, &ASFR_PlayerController::Turn);
    InputComponent->BindAxis("LookUp", this, &ASFR_PlayerController::LookUp);
}