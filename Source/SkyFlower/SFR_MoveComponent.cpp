// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_MoveComponent.h"
#include "SFR_InputHandlerComponent.h"
#include "DebugHelpers.h"
#include "SFR_PlayerController.h"
#include "SFR_PlayerCamera.h"
#include "SFR_Player.h"
#include "Kismet/GameplayStatics.h"


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
	CameraRef = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
}


// Called every frame
void USFR_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//updateMovement()



	//updateGravity()
}

void USFR_MoveComponent::MoveForward(float Value)
{
	if (!IsValid(PlayerRef)) return;
	if (!IsValid(CameraRef)) return;
	const FVector Direction = FRotationMatrix(CameraRef->GetActorRotation()).GetScaledAxis(EAxis::X);
	FVector Offset = Direction * Value * (/*CurrentVelocity*/ CurrentVelocity * /*DeltaTime*/ 1.f);
	PlayerRef->AddActorWorldOffset(Offset);

	if (bDebugLog)
		Debug::PrintFixedLine("ASFR_PlayerCamera::MoveForward  " + Direction.ToString(), 110);
}

void USFR_MoveComponent::MoveRight(float Value)
{
	if (!IsValid(PlayerRef)) return;
	if (!IsValid(CameraRef)) return;
	const FVector Direction = FRotationMatrix(CameraRef->GetActorRotation()).GetScaledAxis(EAxis::Y);
	FVector Offset = Direction * Value * (/*CurrentVelocity*/ CurrentVelocity * /*DeltaTime*/ 1.f);
	PlayerRef->AddActorWorldOffset(Offset);

	if (bDebugLog)
		Debug::PrintFixedLine("ASFR_PlayerCamera::MoveRight  " + Direction.ToString(), 120);
}
