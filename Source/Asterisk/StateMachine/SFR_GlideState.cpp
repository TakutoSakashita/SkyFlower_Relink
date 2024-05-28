// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_GlideState.h"

void USFR_GlideState::OnEnterState()
{
	Super::OnEnterState();

	PlayerStateMachine->MoveState = EMovementState::Glide;
	PlayerStateMachine->bGlide = true;

	SetGlideSpeedBias();
	SetGlideGravityBias();
	SetGlideStopPowerBias();
	SetGlideAirControlledBias();
	ResetAirbornTime();

	//TODO camera work
	CameraRef->SetBoomLength(graid_boom_length_max);
	CameraRef->ResetPitch();
}

void USFR_GlideState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_GlideState::TickState", 100003);
}

void USFR_GlideState::OnExitState()
{
	Super::OnExitState();

	PlayerStateMachine->bGlide = false;
}
