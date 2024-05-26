// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_DashState.h"
#include "../DebugHelpers.h"

void USFR_DashState::OnEnterState()
{
	Super::OnEnterState();

	if (!IsValid(CameraRef)) return;
	if (!IsValid(MoveComponent)) return;

	MoveComponent->MoveState = EMovementState::Dash;

	if (MoveComponent->inputValue.IsZero()) {// air jump
		MoveComponent->AddForce(FVector(0, 0, 1), airJumpPower, airJumpDeceleration);
	}
	else // air dash
	{
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0);
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0);
		FVector moveVector = Fwd * MoveComponent->inputValue.Y + Right * MoveComponent->inputValue.X;
		moveVector.Z += 0.1f;
		MoveComponent->AddForce(moveVector, airDashSpeed, airDashDeceleration);
	}

		CameraRef->ResetBoomLength();
		CameraRef->ResetPitch();

}

void USFR_DashState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_DashState::TickState", 100002);

	if (!MoveComponent->bForce)
		MoveComponent->SwitchStateByKey("Glide");
	
}

void USFR_DashState::OnExitState()
{
	Super::OnExitState();
}

