// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../StateMachine/SFR_StateBase.h"
// player components
#include "SFA_PlayerController.h"
#include "SFA_Camera.h"
#include "SFA_Player.h"
#include "SFA_PlayerMovementComponent.h"
#include "SFA_PlayerStateMachine.h"
#include "SFA_InputHandlerComponent.h"
#include "Kismet/GameplayStatics.h"

#include "SFA_PlayerStateBase.generated.h"



UCLASS()
class ASTERISK_API USFA_PlayerStateBase : public USFR_StateBase
{
	GENERATED_BODY()

public:
	USFA_PlayerStateBase();
	virtual void OnEnterState() override;
	//virtual void TickState(float DeltaTime) override;
	//virtual void OnExitState() override;

	//~Parameters for components
	USFA_PlayerStateMachine* PlayerStateMachine;
	ASFA_Camera* Camera;
	ASFA_Player* Player;
	USFA_InputHandlerComponent* InputHandler;
	USFA_PlayerMovementComponent* PlayerMovementComponent;
	/* animInstance */
	//~End of Parameters for components



};
