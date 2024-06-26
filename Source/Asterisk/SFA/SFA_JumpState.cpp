// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_JumpState.h"

void USFA_JumpState::OnEnterState()
{
	Super::OnEnterState();

	if (PlayerMovementComponent->MovementMode == EMovementMode::MOVE_Walking) {
		Player->Jump();
		return;
	}

	if (PlayerMovementComponent->MovementMode == EMovementMode::MOVE_Falling) {

		PlayerMovementComponent->SetMovementMode(MOVE_Flying);
		PlayerMovementComponent->GravityScale = 0.2f;
	}
	
	PlayerStateMachine->SetDashDistance(AirJumpDistance);
	PlayerStateMachine->SetDashElapsedTime(0.f);
	PlayerStateMachine->SetDashTime(AirJumpTime);
	PlayerStateMachine->SetIsDashing(true);
	PlayerStateMachine->SetDashDirection(AirJumpDirection);

	if (!AirJump_Montage) return;
	Player->GetMesh()->GetAnimInstance()->Montage_Play(AirJump_Montage);
}

void USFA_JumpState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	if (!PlayerStateMachine->GetIsDashing()) {
		PlayerStateMachine->SwitchStateByKey("Float");
	}
}

void USFA_JumpState::OnExitState()
{
	Super::OnExitState();
}
