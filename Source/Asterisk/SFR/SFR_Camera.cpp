// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_Camera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"


ASFR_Camera::ASFR_Camera()
{
	PrimaryActorTick.bCanEverTick = true;

	// Init main camera
	SpringArmMain = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmMain->SetupAttachment(RootComponent);
	SpringArmMain->TargetArmLength = 300.0f; // Adjust as needed
	SpringArmMain->bUsePawnControlRotation = true;

	CameraMain = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraMain->SetupAttachment(SpringArmMain, USpringArmComponent::SocketName);
	CameraMain->bUsePawnControlRotation = false;

	CameraArrowMain = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	CameraArrowMain->SetupAttachment(CameraMain);
	CameraArrowMain->ArrowSize = 0.2f;
	CameraArrowMain->bHiddenInGame = false;
	CameraArrowMain->SetRelativeLocation(FVector(400.f, 0.f, 0.f));

}


void ASFR_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASFR_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowTarget)
	{
		SetActorLocation(FollowTarget->GetActorLocation());
	}

	//update rotation
	float rotateCorrection = 60.f / (1.0f / DeltaTime);
	FRotator rotation = this->GetActorRotation();
	rotation.Pitch = FMath::Clamp(rotation.Pitch + (inputValue.Y * pitch_sensitivity * rotateCorrection), current_pitch_min, current_pitch_max);
	rotation.Yaw += inputValue.X * yaw_sensitivity * rotateCorrection;
	float newLength = (-rotation.Pitch - current_pitch_min) / (current_pitch_max - current_pitch_min) * (current_boom_length_max - default_boom_length_min) + default_boom_length_min;
	SpringArmMain->TargetArmLength = newLength;

}

void ASFR_Camera::SetFollowTarget(AActor* Target)
{
	FollowTarget = Target;
}

void ASFR_Camera::Turn(float value)
{
	//AddControllerYawInput(Value);

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Yaw += value;
	SetActorRotation(CameraRotation);

	inputValue.X = value;
}

void ASFR_Camera::LookUp(float value)
{
	//AddControllerPitchInput(Value);

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch + value, -80.0f, 80.0f);// pitch from -80 to 80 degree
	SetActorRotation(CameraRotation);

	inputValue.Y = value;
}





