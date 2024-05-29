// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_FloatState.h"

void USFR_FloatState::OnEnterState()
{
	Super::OnEnterState();


	if (!IsValid(CameraRef)) return;
	if (!IsValid(PlayerStateMachine)) return;

	PlayerStateMachine->MoveState = ESFR_MoveState::Float;

	ResetSpeedBias();
	ResetGravityBias();
	ResetStopPowerBias();
	ResetAirControlledBias();
	ResetAirbornTime();

	//TODO camera work
	CameraRef->ResetPitch();
	CameraRef->ResetBoomLength();
}

void USFR_FloatState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_FloatingState::TickState", 100001);
}
