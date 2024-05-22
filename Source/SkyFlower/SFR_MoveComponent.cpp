// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_MoveComponent.h"
#include "SFR_InputHandlerComponent.h"
#include "SFR_PlayerCamera.h"
#include "DebugHelpers.h"


USFR_MoveComponent::USFR_MoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USFR_MoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void USFR_MoveComponent::SwitchStateByKey(FString StateKey)
{
	Super::SwitchStateByKey(StateKey);
}

void USFR_MoveComponent::InitStateManager()
{
	Super::InitStateManager();
}

void USFR_MoveComponent::InitializeStates()
{
	Super::InitializeStates();
}

void USFR_MoveComponent::Initialize(ASFR_Player* player, USFR_InputHandlerComponent* inputHandler)
{
	PlayerRef = player;
	InputHandler = inputHandler;
}


// Called every frame
void USFR_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//updateMovement()



	//updateGravity()
}

//
//void USFR_MoveComponent::MoveForward(float Value)
//{
//
//	if (!IsValid(InputHandler->PlayerPawn)) return;
//	const FVector Direction = FRotationMatrix(InputHandler->Camera->GetActorRotation()).GetScaledAxis(EAxis::X);
//	FVector Offset = Direction * Value * (/*CurrentVelocity*/ 1.f * /*DeltaTime*/ 1.f);
//	InputHandler->PlayerPawn->AddActorWorldOffset(Offset);
//	Debug::PrintFixedLine("ASFR_PlayerCamera::MoveForward  " + Direction.ToString(), 110);
//}
//
//void USFR_MoveComponent::MoveRight(float Value)
//{
//
//	if (!IsValid(InputHandler->PlayerPawn)) return;
//	const FVector Direction = FRotationMatrix(InputHandler->Camera->GetActorRotation()).GetScaledAxis(EAxis::Y);
//	FVector Offset = Direction * Value * (/*CurrentVelocity*/ 1.f * /*DeltaTime*/ 1.f);
//	InputHandler->PlayerPawn->AddActorWorldOffset(Offset);
//	Debug::PrintFixedLine("ASFR_PlayerCamera::MoveRight  " + Direction.ToString(), 120);
//}
