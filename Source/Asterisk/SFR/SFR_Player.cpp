// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_Player.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SFR_InputHandlerComponent.h"
#include "../StateMachine/SFR_PlayerStateMachine.h"

ASFR_Player::ASFR_Player()
{
	PrimaryActorTick.bCanEverTick = false;

	InputHandler = CreateDefaultSubobject<USFR_InputHandlerComponent>(TEXT("InputHandler"));
	PlayerStateMachine = CreateDefaultSubobject<USFR_PlayerStateMachine>(TEXT("PlayerStateMachine"));

	// Create Capsule Component and set it as Root Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
	RootComponent = CapsuleComponent;

	// Create Skeletal Mesh Component and attach it to Capsule Component
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

}

void ASFR_Player::BeginPlay()
{
	Super::BeginPlay();
	InputHandler->Initialize(this);
	//PlayerStateMachine->Initialize(this);
	//PlayerStateMachine->InitStateManager();
}

void ASFR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASFR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!IsValid(InputHandler)) return;

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputHandler->SetupPlayerInputComponent(PlayerInputComponent);
}

