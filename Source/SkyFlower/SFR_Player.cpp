// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_Player.h"
#include "SFR_InputHandlerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SFR_MoveComponent.h"
#include "SFR_ActionComponent.h"

// Sets default values
ASFR_Player::ASFR_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InputHandler = CreateDefaultSubobject<USFR_InputHandlerComponent>(TEXT("InputHandler"));
	MoveComponent = CreateDefaultSubobject<USFR_MoveComponent>(TEXT("MoveComponent"));
	ActionComponent = CreateDefaultSubobject<USFR_ActionComponent>(TEXT("ActionComponent"));

	// Create Capsule Component and set it as Root Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
	RootComponent = CapsuleComponent;

	// Create Skeletal Mesh Component and attach it to Capsule Component
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
}

// Called when the game starts or when spawned
void ASFR_Player::BeginPlay()
{
	Super::BeginPlay();

	InputHandler->Initialize(this);
	MoveComponent->Initialize(this, InputHandler);
	MoveComponent->InitStateManager();
}

// Called every frame
void ASFR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASFR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!IsValid(InputHandler)) return;

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputHandler->SetupPlayerInputComponent(PlayerInputComponent);
}

