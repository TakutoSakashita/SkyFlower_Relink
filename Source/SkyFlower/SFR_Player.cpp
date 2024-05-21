// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_Player.h"
#include "SFR_InputHandlerComponent.h"

// Sets default values
ASFR_Player::ASFR_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InputComp = CreateDefaultSubobject<USFR_InputHandlerComponent>(TEXT("InputComp"));
}

// Called when the game starts or when spawned
void ASFR_Player::BeginPlay()
{
	Super::BeginPlay();
	InputComp->Initialize(this);
	
}

// Called every frame
void ASFR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASFR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!IsValid(InputComp)) return;

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComp->SetupPlayerInputComponent(PlayerInputComponent);
}

