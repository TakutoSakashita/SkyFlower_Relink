// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_StunState.h"

void USFA_StunState::OnEnterState()
{
	Super::OnEnterState();

	InputHandler->bCanMove = false;
	InputHandler->bCanAttack = false;
	Player->PlayerState = ESFA_PlayerState::Invincible;

	//stun 1 second 
	FTimerDelegate DelegateStun;
	DelegateStun.BindLambda([&]()
	{
		InputHandler->bCanMove = true;
		InputHandler->bCanAttack = true;
	});
	FTimerHandle TimerHandleStun;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleStun, DelegateStun, 1.f, false);

	//Invincible 2 second
	FTimerDelegate DelegateInvincible;
	DelegateInvincible.BindLambda([&]()
	{
		Player->PlayerState = ESFA_PlayerState::Damageable;
		PlayerStateMachine->SwitchStateByKey("Float");
	});
	FTimerHandle TimerHandleInvincible;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleInvincible, DelegateInvincible, 2.f, false);
}

void USFA_StunState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
}

void USFA_StunState::OnExitState()
{
	Super::OnExitState();
	InputHandler->bCanMove = true;
	InputHandler->bCanAttack = true;
	Player->PlayerState = ESFA_PlayerState::Damageable;
}
