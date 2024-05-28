// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_Camera.h"

// Sets default values
ASFR_Camera::ASFR_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASFR_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASFR_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASFR_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

