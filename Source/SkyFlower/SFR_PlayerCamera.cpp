// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "DebugHelpers.h"

// Sets default values
ASFR_PlayerCamera::ASFR_PlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	// Init main camera
	SpringArmMain = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmMain"));
	SpringArmMain->SetupAttachment(RootComponent);
	SpringArmMain->TargetArmLength = 300.0f; // Adjust as needed
	SpringArmMain->bUsePawnControlRotation = true;

	CameraMain = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
	CameraMain->SetupAttachment(SpringArmMain, USpringArmComponent::SocketName);
	CameraMain->bUsePawnControlRotation = false;

	CameraArrowMain = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraArrowMain"));
	CameraArrowMain->SetupAttachment(CameraMain);
	CameraArrowMain->ArrowSize = 0.2f;
	CameraArrowMain->bHiddenInGame = false;
	CameraArrowMain->SetRelativeLocation(FVector(400.f, 0.f, 0.f));

}

// Called when the game starts or when spawned
void ASFR_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASFR_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowTarget)
	{
		SetActorLocation(FollowTarget->GetActorLocation());
	}
}

void ASFR_PlayerCamera::SetFollowTarget(AActor* Target)
{
	FollowTarget = Target;
}

void ASFR_PlayerCamera::Turn(float Value)
{

	Debug::PrintFixedLine("ASFR_PlayerCamera::Turn  ", 104);

	//AddControllerYawInput(Value);

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Yaw += Value;
	SetActorRotation(CameraRotation);
}

void ASFR_PlayerCamera::LookUp(float Value)
{
	Debug::PrintFixedLine("ASFR_PlayerCamera::LookUp  ", 105);

	//AddControllerPitchInput(Value);

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch + Value, -80.0f, 80.0f);// pitch from -80 to 80 degree
	SetActorRotation(CameraRotation);
}
