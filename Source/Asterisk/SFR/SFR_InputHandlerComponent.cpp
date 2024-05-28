// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_InputHandlerComponent.h"
#include "SFR_Camera.h"
#include "SFR_Player.h"
#include "SFR_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../StateMachine/SFR_PlayerStateMachine.h"
#include "../DebugHelpers.h"

USFR_InputHandlerComponent::USFR_InputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USFR_InputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USFR_InputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void USFR_InputHandlerComponent::Initialize(AActor* player)
{
	if (!IsValid(player)) return;

	Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	ensure(Camera);

	Player = Cast<ASFR_Player>(player);
	ensure(Player);

	PlayerStateMachine = Player->PlayerStateMachine;

}
void USFR_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &USFR_InputHandlerComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &USFR_InputHandlerComponent::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &USFR_InputHandlerComponent::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &USFR_InputHandlerComponent::LookUp);

	PlayerInputComponent->BindAction("Key_E", IE_Pressed, this, &USFR_InputHandlerComponent::Key_E_Pressed);
	PlayerInputComponent->BindAction("Key_E", IE_Released, this, &USFR_InputHandlerComponent::Key_E_Released);
}


void USFR_InputHandlerComponent::MoveForward(float Value)
{
	if (!IsValid(PlayerStateMachine)) return;
	if (InputState == EInputState::Move_disable) return;

	//PlayerStateMachine->AddForwardMovementInput(Value);
}

void USFR_InputHandlerComponent::MoveRight(float Value)
{
	if (!IsValid(PlayerStateMachine)) return;
	if (InputState == EInputState::Move_disable) return;

	//PlayerStateMachine->AddRightMovementInput(Value);
}

void USFR_InputHandlerComponent::Turn(float Value)
{
	if (!IsValid(Camera))
		Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	if (!IsValid(Camera)) return;
	Camera->Turn(Value);
}

void USFR_InputHandlerComponent::LookUp(float Value)
{
	if (!IsValid(Camera))
		Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	if (!IsValid(Camera)) return;
	Camera->LookUp(Value);
}

void USFR_InputHandlerComponent::Key_E_Pressed()
{
	if (!IsValid(PlayerStateMachine)) return;
	if (InputState == EInputState::Move_disable) return;

	//PlayerStateMachine->SwitchStateByKey("Dash");

	Debug::PrintFixedLine("Key_E_Pressed", 120);
}

void USFR_InputHandlerComponent::Key_E_Released()
{
	if (!IsValid(PlayerStateMachine)) return;
	if (InputState == EInputState::Move_disable) return;

	//PlayerStateMachine->SwitchStateByKey("Float");

	Debug::PrintFixedLine("Key_E_Released", 120);
}




