// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"

#define TIME UGameplayStatics::GetGlobalTimeDilation(GetWorld())

void USFR_PlayerStateBase::OnEnterState()
{
	Super::OnEnterState();

	CameraRef = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	PlayerRef = Cast<ASFR_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(PlayerRef)) {
		InputHandlerRef = PlayerRef->InputHandler;
		MoveComponent = PlayerRef->MoveComponent;
	}

}

void USFR_PlayerStateBase::UpdateRootMotion(float DeltaTime)
{
	return MoveComponent->UpdateRootMotion(DeltaTime);
}

void USFR_PlayerStateBase::UpdateMove(float DeltaTime)
{
	return MoveComponent->UpdateMove(DeltaTime);
}

void USFR_PlayerStateBase::UpdateForce(float DeltaTime)
{
	return MoveComponent->UpdateForce(DeltaTime);
}

void USFR_PlayerStateBase::UpdateFly(float DeltaTime)
{
	return MoveComponent->UpdateFly(DeltaTime);
}

void USFR_PlayerStateBase::UpdateGravity(float DeltaTime)
{
	return MoveComponent->UpdateGravity(DeltaTime);
}

void USFR_PlayerStateBase::UpdateRotation(float DeltaTime)
{
	return MoveComponent->UpdateRotation(DeltaTime);
}

bool USFR_PlayerStateBase::SweepMove(FVector MoveVector, float MoveSpeed)
{
	return MoveComponent->SweepMove(MoveVector, MoveSpeed);
}

FVector USFR_PlayerStateBase::GetAlongWallVector(FVector_NetQuantizeNormal HitNormal, FVector MoveVector)
{
	return MoveComponent->GetAlongWallVector(HitNormal, MoveVector);
}


