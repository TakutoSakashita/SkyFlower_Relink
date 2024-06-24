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

	AimTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AimTimeline"));
	BoostTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("BoostTimeline"));
}

void ASFA_Camera::BeginPlay()
{
	Super::BeginPlay();

	Camera->SetRelativeLocation(InitialCameraOffset);
	
	if (AimFloatCurve)
	{
		AimInterpFunction.BindUFunction(this, FName("AimingProcess"));
		AimTimeline->AddInterpFloat(AimFloatCurve, AimInterpFunction);
		AimTimeline->SetLooping(false);
		AimTimeline->SetTimelineLength(AimTimeLineLength);
	}

	if (BoostFloatCurve)
	{
		BoostInterpFunction.BindUFunction(this, FName("BoostingProcess"));
		BoostTimeline->AddInterpFloat(BoostFloatCurve, BoostInterpFunction);
		BoostTimeline->SetLooping(false);
		BoostTimeline->SetTimelineLength(BoostTimeLineLength);
	}
}

void ASFA_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation();

	if (AimTimeline)
	{
		AimTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
	}

	if (BoostTimeline)
	{
		BoostTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
	}
}

void ASFA_Camera::AimingProcess(float Value)
{
	SpringArm->TargetArmLength = FMath::Lerp(InitialSpringArmLength, AimSpringArmLength, Value);
	Camera->FieldOfView = FMath::Lerp(InitialFOV, AimFOV, Value);
	Camera->SetRelativeLocation(FMath::Lerp(InitialCameraOffset, AimCameraOffset, Value));

	AimCurrentTimelinePosition = AimTimeline->GetPlaybackPosition();
}

void ASFA_Camera::StartAim()
{
	if (!AimFloatCurve) return;
	if (!AimTimeline) return;

	if (AimTimeline->GetPlaybackPosition() == 0.0f || AimTimeline->GetPlaybackPosition() == AimTimeLineLength){
		AimTimeline->PlayFromStart();
	}
	else{
		AimTimeline->Play();
	}
}

void ASFA_Camera::EndAim()
{
	if (!AimFloatCurve) return;
	if (!AimTimeline) return;

	if (AimTimeline->GetPlaybackPosition() == 0.0f || AimTimeline->GetPlaybackPosition() == AimTimeLineLength){
		AimTimeline->ReverseFromEnd();
	}
	else{
		AimTimeline->Reverse();
	}
}

void ASFA_Camera::BoostingProcess(float Value)
{
	SpringArm->TargetArmLength = FMath::Lerp(InitialSpringArmLength, BoostSpringArmLength, Value);
	Camera->FieldOfView = FMath::Lerp(InitialFOV, BoostFOV, Value);
	Camera->SetRelativeLocation(FMath::Lerp(InitialCameraOffset, BoostCameraOffset, Value));

	BoostCurrentTimelinePosition = BoostTimeline->GetPlaybackPosition();
}

void ASFA_Camera::StartBoost()
{
	if (!BoostFloatCurve) return;
	if (!BoostTimeline) return;

	if (BoostTimeline->GetPlaybackPosition() == 0.0f || BoostTimeline->GetPlaybackPosition() == BoostTimeLineLength){
		BoostTimeline->PlayFromStart();
	}
	else{
		BoostTimeline->Play();
	}
}

void ASFA_Camera::EndBoost()
{
	if (!BoostFloatCurve) return;
	if (!BoostTimeline) return;

	if (BoostTimeline->GetPlaybackPosition() == 0.0f || BoostTimeline->GetPlaybackPosition() == BoostTimeLineLength){
		BoostTimeline->ReverseFromEnd();
	}
	else{
		BoostTimeline->Reverse();
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

FVector ASFA_Camera::GetCameraCompForwardVector() const
{
	return GetActorForwardVector();
}

FVector ASFA_Camera::GetCameraCompLocation() const
{
	return Camera->GetComponentLocation();
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



