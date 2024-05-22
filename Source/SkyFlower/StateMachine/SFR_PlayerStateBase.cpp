// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerStateBase.h"
#include "../SFR_MoveComponent.h"
#include "../SFR_ActionComponent.h"
#include "../SFR_PlayerController.h"
#include "../SFR_PlayerCamera.h"
#include "../SFR_Player.h"
#include "Kismet/GameplayStatics.h"


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


