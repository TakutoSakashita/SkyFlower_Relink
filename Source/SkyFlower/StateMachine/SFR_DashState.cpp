// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_DashState.h"
#include "../DebugHelpers.h"

void USFR_DashState::OnEnterState()
{
	Super::OnEnterState();


	if (IsValid(CameraRef))
	{
		// カメラベクトル
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0);
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0);
		// 移動方向
		FVector moveVector = Fwd * MoveComponent->inputValue.Y + Right * MoveComponent->inputValue.X;
		moveVector.Z += 0.1f;
		MoveComponent->AddForce(moveVector, airDashSpeed, airDashDeceleration);

		CameraRef->ResetBoomLength();
		CameraRef->ResetPitch();
	}

	timer = 1.0f;
}

void USFR_DashState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_DashState::TickState", 100002);

	UpdateRootMotion(DeltaTime);
	UpdateMove(DeltaTime);
	UpdateForce(DeltaTime);
	UpdateFly(DeltaTime);
	UpdateGravity(DeltaTime);
	UpdateRotation(DeltaTime);

	timer -= DeltaTime;
	if (timer < 0.f)
		MoveComponent->SwitchStateByKey("Float");
}

void USFR_DashState::OnExitState()
{
	ResetSpeedBias();
	ResetGravityBias();
	ResetStopPowerBias();
	ResetAirControlledBias();
	ResetAirbornTime();

	//TODO camera work
	CameraRef->ResetPitch();
	CameraRef->ResetBoomLength();
}

