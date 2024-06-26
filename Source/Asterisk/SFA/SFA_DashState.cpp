// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_DashState.h"


void USFA_DashState::OnEnterState()
{
	Super::OnEnterState();
	
	//DashDirection = FVector(Player->GetVelocity().X, Player->GetVelocity().Y, 0.f);
	DashDirection = FVector(Player->GetActorForwardVector().X, Player->GetActorForwardVector().Y, 0.f);
	
	PlayerStateMachine->SetDashDistance(DashDistance);
	PlayerStateMachine->SetDashElapsedTime(0.f);
	PlayerStateMachine->SetDashTime(DashTime);
	PlayerStateMachine->SetIsDashing(true);
	PlayerStateMachine->SetDashDirection(DashDirection);

	if (!Dash_Montage) return;
	Player->GetMesh()->GetAnimInstance()->Montage_Play(Dash_Montage);
}

void USFA_DashState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	if (!PlayerStateMachine->GetIsDashing()) {
		PlayerStateMachine->SwitchStateByKey("Float");
	}
}

void USFA_DashState::OnExitState()
{
	Super::OnExitState();

}
