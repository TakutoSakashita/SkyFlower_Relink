// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_GlindState.h"

void USFR_GlindState::OnEnterState()
{
	Super::OnEnterState();

	MoveComponent->MoveState = EMovementState::Glide;

	SetGraidSpeedBias();
	SetGraidGravityBias();
	SetGraidStopPowerBias();
	SetGraidAirControlledBias();
	ResetAirbornTime();

	//TODO camera work
	//CameraRef->SetGraidBoomLength();
	//CameraRef->ResetPitch();
}

void USFR_GlindState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_GlindState::TickState", 100003);

	UpdateRootMotion(DeltaTime);
	UpdateMove(DeltaTime);
	UpdateForce(DeltaTime);
	UpdateFly(DeltaTime);
	UpdateGravity(DeltaTime);
	UpdateRotation(DeltaTime);
}

void USFR_GlindState::OnExitState()
{
	ResetSpeedBias();
	ResetGravityBias();
	ResetStopPowerBias();
	ResetAirControlledBias();
	ResetAirbornTime();

	//TODO camera work
	//CameraRef->ResetPitch();
	//CameraRef->ResetBoomLength();
}
