// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_Camera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

//debug
#include "../DebugHelpers.h"


ASFA_Camera::ASFA_Camera()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraArrowMain = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraArrowMain"));
	CameraArrowMain->SetupAttachment(RootComponent);
	CameraArrowMain->ArrowSize = 2.f;
	CameraArrowMain->bHiddenInGame = false;

	SpringArmMain = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmMain"));
	SpringArmMain->SetupAttachment(CameraArrowMain);
	SpringArmMain->TargetArmLength = 400.0f; // Adjust as needed
	SpringArmMain->bUsePawnControlRotation = true;

	CameraMain = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
	CameraMain->SetupAttachment(SpringArmMain, USpringArmComponent::SocketName);
	CameraMain->bUsePawnControlRotation = false;

	//CameraMain->bCameraMeshHiddenInGame = false;

}

void ASFA_Camera::BeginPlay()
{
	Super::BeginPlay();

}

void ASFA_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation();

}

void ASFA_Camera::Turn(float value)
{
	//AddControllerYawInput(2.f /*yawSensitivity*/ * value * GetWorld()->GetDeltaSeconds());

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Yaw += 1.f /*yawSensitivity*/ * value;
	SetActorRotation(CameraRotation);


}

void ASFA_Camera::LookUp(float value)
{
	//AddControllerPitchInput(2.f /*pitchSensitivity*/ * value * GetWorld()->GetDeltaSeconds());

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Pitch += 1.f /*pitchSensitivity*/ * value;
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch, -80.0f, 80.0f);// pitch from -80 to 80 degree
	SetActorRotation(CameraRotation);


}

void ASFA_Camera::UpdateLocation()
{
	if (!IsValid(FollowTarget)) return;
	FVector targetPos = FollowTarget->GetActorLocation();
	FVector cameraPos = FVector(
		targetPos.X,
		targetPos.Y,
		targetPos.Z + 50.f /* set camera higher than player pos */
	);
	SetActorLocation(cameraPos);

	//SetActorLocation(FollowTarget->GetActorLocation());
}



