// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_InputHandlerComponent.h"
#include "DebugHelpers.h"
#include "SFR_MoveComponent.h"
#include "SFR_ActionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SFR_PlayerController.h"
#include "SFR_PlayerCamera.h"
#include "SFR_Player.h"


USFR_InputHandlerComponent::USFR_InputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USFR_InputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USFR_InputHandlerComponent::Initialize(AActor* player)
{
	if (!IsValid(player)) return;

	Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	ensure(Camera);

	Player = Cast<ASFR_Player>(player);
	ensure(Player);

	MoveComponent = Player->MoveComponent;
	ActionComponent = Player->ActionComponent;
}

void USFR_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Debug::Print("USFR_InputHandlerComponent::SetupPlayerInputComponent");

	PlayerInputComponent->BindAxis("MoveForward", this, &USFR_InputHandlerComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &USFR_InputHandlerComponent::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &USFR_InputHandlerComponent::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &USFR_InputHandlerComponent::LookUp);

	PlayerInputComponent->BindAction("Key_E", IE_Pressed, this, &USFR_InputHandlerComponent::Key_E_Pressed);
	PlayerInputComponent->BindAction("Key_E", IE_Released, this, &USFR_InputHandlerComponent::Key_E_Released);

	PlayerInputComponent->BindAction("Shift", IE_Pressed, this, &USFR_InputHandlerComponent::Shift_Pressed);

}


// Called every frame
void USFR_InputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDebugLog)
		Debug::PrintFixedLine("USFR_InputHandlerComponent::TickComponent", 101);

	if (!IsValid(Camera))
		Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();

}


void USFR_InputHandlerComponent::MoveForward(float Value)
{
	if (!IsValid(MoveComponent)) return;
	//check InputState
	if (InputState == EInputState::Move_disable) return;

	MoveComponent->AddForwardMovementInput(Value);
}

void USFR_InputHandlerComponent::MoveRight(float Value)
{
	if (!IsValid(MoveComponent)) return;
	if (InputState == EInputState::Move_disable) return;

	MoveComponent->AddRightMovementInput(Value);
}

void USFR_InputHandlerComponent::Turn(float Value)
{
	if (!IsValid(Camera)) return;

	Camera->Turn(Value);
}

void USFR_InputHandlerComponent::LookUp(float Value)
{
	if (!IsValid(Camera)) return;

	Camera->LookUp(Value);
}

void USFR_InputHandlerComponent::Key_E_Pressed()
{
	if (!IsValid(MoveComponent)) return;
	if (InputState == EInputState::Move_disable) return;

	MoveComponent->SwitchStateByKey("Dash");

	Debug::PrintFixedLine("Key_E_Pressed", 120);
}

void USFR_InputHandlerComponent::Key_E_Released()
{
	if (!IsValid(MoveComponent)) return;
	if (InputState == EInputState::Move_disable) return;

	MoveComponent->SwitchStateByKey("Float");

	Debug::PrintFixedLine("Key_E_Released", 120);

}

void USFR_InputHandlerComponent::Shift_Pressed()
{
	if (!IsValid(MoveComponent)) return;
	if (InputState == EInputState::Move_disable) return;

	//MoveComponent->SwitchStateByKey("Dash");

	//Debug::PrintFixedLine("Shift_Pressed", 120);

}

