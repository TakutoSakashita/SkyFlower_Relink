// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_DashState.h"

void USFR_DashState::OnEnterState()
{
	Super::OnEnterState();

	if (!IsValid(CameraRef)) return;
	if (!IsValid(PlayerStateMachine)) return;

	PlayerStateMachine->MoveState = EMovementState::Dash;

	if (PlayerStateMachine->inputValue.IsZero()) {// air jump
		PlayerStateMachine->AddForce(FVector(0, 0, 1), airJumpPower, airJumpDeceleration);
	}
	else // air dash
	{
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0);
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0);
		FVector moveVector = Fwd * PlayerStateMachine->inputValue.Y + Right * PlayerStateMachine->inputValue.X;
		moveVector.Z += 0.1f;
		PlayerStateMachine->AddForce(moveVector, airDashSpeed, airDashDeceleration);
	}

	CameraRef->ResetBoomLength();
	CameraRef->ResetPitch();
}

void USFR_DashState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_DashState::TickState", 100002);

	if (!PlayerStateMachine->bForce)
		PlayerStateMachine->SwitchStateByKey("Glide");
}

