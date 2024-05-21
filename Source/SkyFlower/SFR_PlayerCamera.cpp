// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

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

    CameraArrowMain = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraArrowMain"));
    CameraArrowMain->SetupAttachment(CameraMain);
    CameraArrowMain->ArrowSize = 2.0f;
    CameraArrowMain->bHiddenInGame = false;

    //// Initialize LeftSpringArm and CameraLeft (left side view)
    //SpringArmLeft = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmLeft"));
    //SpringArmLeft->SetupAttachment(RootComponent);
    //SpringArmLeft->TargetArmLength = 300.0f; // Adjust as needed
    //SpringArmLeft->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); // Face the player from the side
    //SpringArmLeft->bUsePawnControlRotation = false;

    //CameraLeft = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraLeft"));
    //CameraLeft->SetupAttachment(SpringArmLeft, USpringArmComponent::SocketName);

    //CameraArrowLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraArrowLeft"));
    //CameraArrowLeft->SetupAttachment(CameraLeft);
    //CameraArrowLeft->ArrowSize = 2.0f;
    //CameraArrowLeft->bHiddenInGame = false;

    //// Initialize SpringArmRight and CameraRight (right side view)
    //SpringArmRight = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmRight"));
    //SpringArmRight->SetupAttachment(RootComponent);
    //SpringArmRight->TargetArmLength = 300.0f; // Adjust as needed
    //SpringArmRight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); // Face the player from the side
    //SpringArmRight->bUsePawnControlRotation = false;

    //CameraRight = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraRight"));
    //CameraRight->SetupAttachment(SpringArmRight, USpringArmComponent::SocketName);

    //CameraArrowRight = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraArrowRight"));
    //CameraArrowRight->SetupAttachment(CameraRight);
    //CameraArrowRight->ArrowSize = 2.0f;
    //CameraArrowRight->bHiddenInGame = false;
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