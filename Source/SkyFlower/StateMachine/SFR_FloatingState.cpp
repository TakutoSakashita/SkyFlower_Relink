// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_FloatingState.h"
#include "../DebugHelpers.h"

void USFR_FloatingState::OnEnterState()
{
	Super::OnEnterState();

	/* derived from StateBase */
	//bCanTickState = true;
	//bCanRepeat = false;
	StateDisplayName = "Float";

	/* derived from PlayerStateBase */
	//ASFR_PlayerCamera* CameraRef = nullptr;
	//ASFR_Player* PlayerRef = nullptr;
	//USFR_InputHandlerComponent* InputHandlerRef = nullptr;
	//USFR_MoveComponent* MoveComponent = nullptr;
}

void USFR_FloatingState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_FloatingState::TickState");
	//process gravity

}