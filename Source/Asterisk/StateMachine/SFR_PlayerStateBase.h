// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_StateBase.h"
#include "../SFR/SFR_PlayerController.h"
#include "../SFR/SFR_Camera.h"
#include "../SFR/SFR_Player.h"
#include "../SFR/SFR_InputHandlerComponent.h"
#include "../StateMachine/SFR_PlayerStateMachine.h"
#include "../DebugHelpers.h"
#include "SFR_PlayerStateBase.generated.h"


class ASFR_Camera;
class ASFR_Player;
class USFR_InputHandlerComponent;
class USFR_PlayerStateMachine;

UCLASS()
class ASTERISK_API USFR_PlayerStateBase : public USFR_StateBase
{
	GENERATED_BODY()
	
public:
	ASFR_Camera* CameraRef = nullptr;
	ASFR_Player* PlayerRef = nullptr;
	USFR_InputHandlerComponent* InputHandlerRef = nullptr;
	USFR_PlayerStateMachine* PlayerStateMachine = nullptr;
	//actionComponent

	virtual void OnEnterState()override;
	//virtual void TickState(float DeltaTime)override;
	//virtual void OnExitState()override;

	virtual void ResetSpeedBias() { PlayerStateMachine->ResetSpeedBias(); }
	virtual void ResetGravityBias() { PlayerStateMachine->ResetGravityBias(); }
	virtual void ResetStopPowerBias() { PlayerStateMachine->ResetStopPowerBias(); }
	virtual void ResetAirControlledBias() { PlayerStateMachine->ResetAirControlledBias(); }
	virtual void ResetAirbornTime() { PlayerStateMachine->ResetAirbornTime(); }

};
