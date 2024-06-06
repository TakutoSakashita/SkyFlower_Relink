// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_DashState.h"



void USFA_DashState::OnEnterState()
{
	Super::OnEnterState();

	const FVector2D VelocityXY = FVector2D(
		PlayerMovementComponent->GetLastUpdateVelocity().X,
		PlayerMovementComponent->GetLastUpdateVelocity().Y);
	const bool IsMoving = VelocityXY.Size() > 0.1f /*MIN_VALID_MAGNITUDE*/;

	if (PlayerMovementComponent->MovementMode == EMovementMode::MOVE_Walking) {
		Player->Jump();
		return;
	}

	if (PlayerMovementComponent->MovementMode == EMovementMode::MOVE_Falling) {

		PlayerMovementComponent->SetMovementMode(MOVE_Flying);
		PlayerMovementComponent->GravityScale = 0.2f;
	}

	FVector DashDirection = FVector::UpVector;
	if (Player->GetLastMovementInputVector().Size() > 0.1f /*MIN_VALID_MAGNITUDE*/) {
		DashDirection = FVector(Player->GetVelocity().X, Player->GetVelocity().Y, 0.f);
	}
	PlayerStateMachine->SetDashDirection(DashDirection);
	PlayerStateMachine->SetIsDashing(true);
	PlayerStateMachine->SetDashElapsedTime(0.f);

	//todo playMontage
	if (!Dash_AirJump_Montage) return;
	Player->GetMesh()->GetAnimInstance()->Montage_Play(Dash_AirJump_Montage);
}

void USFA_DashState::TickState(float DeltaTime)
{
	if (!PlayerStateMachine->GetIsDashing()) {
		PlayerStateMachine->SwitchStateByKey("float");
	}
}

void USFA_DashState::OnExitState()
{
	Super::OnExitState();

}
