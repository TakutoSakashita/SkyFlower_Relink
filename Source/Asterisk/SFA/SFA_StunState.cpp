// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_StunState.h"

void USFA_StunState::OnEnterState()
{
	Super::OnEnterState();

	InputHandler->bCanAttack = false;
	InputHandler->bCanAttack = false;
	Player->PlayerState = ESFA_PlayerState::Invincible;

	//stun 1 second and back to floatState
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
	{
		PlayerStateMachine->SwitchStateByKey("Float");
	});
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, 1.f, false);
}

void USFA_StunState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
}

void USFA_StunState::OnExitState()
{
	Super::OnExitState();
	InputHandler->bCanAttack = true;
	InputHandler->bCanAttack = true;
	Player->PlayerState = ESFA_PlayerState::Damageable;
}
