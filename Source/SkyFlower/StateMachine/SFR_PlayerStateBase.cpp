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


