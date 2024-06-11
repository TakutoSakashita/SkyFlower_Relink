// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_PlayerStateBase.h"

//
//void USFA_PlayerStateBase::TickState(float DeltaTime)
//{
//	DEBUG_FIXED("USFA_PlayerStateBase::TickState", 600)
//}

USFA_PlayerStateBase::USFA_PlayerStateBase()
{

}

void USFA_PlayerStateBase::OnEnterState()
{
	Super::OnEnterState();
	Camera = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	InputHandler = Player->GetInputHandler();
	PlayerStateMachine = Player->GetPlayerStateMachine();
	PlayerMovementComponent = Player->GetPlayerMovement();
}
