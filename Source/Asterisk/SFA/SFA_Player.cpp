// Fill out your copyright notice in the Description page of Project Settings.



#include "SFA_Player.h"
#include "Components/CapsuleComponent.h"

//custom actor component
#include "SFA_InputHandlerComponent.h"
#include "SFA_PlayerMovementComponent.h"
#include "SFA_PlayerStateMachine.h"



ASFA_Player::ASFA_Player(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USFA_PlayerMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	InputHandler = CreateDefaultSubobject<USFA_InputHandlerComponent>(TEXT("InputHandler"));
	PlayerStateMachine = CreateDefaultSubobject<USFA_PlayerStateMachine>(TEXT("PlayerStateMachine"));
	PlayerMovement = Cast<USFA_PlayerMovementComponent>(GetCharacterMovement());

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f); // at this rotation rate

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}


void ASFA_Player::BeginPlay()
{
	Super::BeginPlay();

}


void ASFA_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASFA_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputHandler->SetupPlayerInputComponent(PlayerInputComponent);
}
