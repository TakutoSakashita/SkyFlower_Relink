// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_Camera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

//debug
#include "../DebugHelpers.h"
#include "Kismet/KismetMathLibrary.h" 

ASFA_Camera::ASFA_Camera()
{
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->ArrowSize = 2.f;
	Arrow->bHiddenInGame = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Arrow);
	SpringArm->TargetArmLength = InitialSpringArmLength; // Adjust as needed
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = InitialFOV;
	Camera->SetRelativeLocation(InitialCameraOffset);
	//CameraMain->bCameraMeshHiddenInGame = false;

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void ASFA_Camera::BeginPlay()
{
	Super::BeginPlay();

	Camera->SetRelativeLocation(InitialCameraOffset);
	
	if (FloatCurve)
	{
		InterpFunction.BindUFunction(this, FName("AimingProcess"));
		Timeline->AddInterpFloat(FloatCurve, InterpFunction);
		Timeline->SetLooping(false);
		Timeline->SetTimelineLength(TimeLineLength);
	}
}

void ASFA_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation();

	if (Timeline)
	{
		Timeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
	}
}

void ASFA_Camera::AimingProcess(float Value)
{
	SpringArm->TargetArmLength = FMath::Lerp(InitialSpringArmLength, AimSpringArmLength, Value);
	Camera->FieldOfView = FMath::Lerp(InitialFOV, AimFOV, Value);
	Camera->SetRelativeLocation(FMath::Lerp(InitialCameraOffset, AimCameraOffset, Value));

	CurrentTimelinePosition = Timeline->GetPlaybackPosition();
}

void ASFA_Camera::StartAim()
{
	if (!FloatCurve) return;
	if (!Timeline) return;

	if (Timeline->GetPlaybackPosition() == 0.0f || Timeline->GetPlaybackPosition() == TimeLineLength){
		Timeline->PlayFromStart();
	}
	else{
		Timeline->Play();
	}
}

void ASFA_Camera::EndAim()
{
	if (!FloatCurve) return;
	if (!Timeline) return;

	if (Timeline->GetPlaybackPosition() == 0.0f || Timeline->GetPlaybackPosition() == TimeLineLength){
		Timeline->ReverseFromEnd();
	}
	else{
		Timeline->Reverse();
	}
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
	/*
	FVector targetPos = FollowTarget->GetActorLocation();
	FVector cameraPos = FVector(
		targetPos.X,
		targetPos.Y,
		targetPos.Z 
	);
	SetActorLocation(cameraPos);
	*/
	SetActorLocation(FollowTarget->GetActorLocation());
}



