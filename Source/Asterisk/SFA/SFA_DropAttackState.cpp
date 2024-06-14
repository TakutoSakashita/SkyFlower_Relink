// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_DropAttackState.h"

void USFA_DropAttackState::OnEnterState()
{
	Super::OnEnterState();

	PlayerStateMachine->SetDashDistance(DashDistance);
	PlayerStateMachine->SetDashElapsedTime(0.f);
	PlayerStateMachine->SetDashTime(DashTime);
	PlayerStateMachine->SetIsDashing(true);
	PlayerStateMachine->SetDashDirection(DashDirection);

	//playMontage
	if (!DropAttack_Montage) return;
	Player->GetMesh()->GetAnimInstance()->Montage_Play(DropAttack_Montage);

}

void USFA_DropAttackState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	if (PlayerMovementComponent->MovementMode == EMovementMode::MOVE_Walking) {
		Player->GetMesh()->GetAnimInstance()->Montage_Stop(0.2);
		Player->Jump();
		PlayerStateMachine->SwitchStateByKey("Float");
	}
}

void USFA_DropAttackState::OnExitState()
{
	Super::OnExitState();
	//stop montage
	//if (Player->GetMesh()->GetAnimInstance()->Montage_IsPlaying(DropAttack_Montage)) {
	//	Player->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, DropAttack_Montage);
	//}
}
