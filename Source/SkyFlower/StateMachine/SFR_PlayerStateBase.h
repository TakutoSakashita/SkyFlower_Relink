// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_StateBase.h"
#include "../SFR_MoveComponent.h"
#include "../SFR_ActionComponent.h"
#include "../SFR_PlayerController.h"
#include "../SFR_PlayerCamera.h"
#include "../SFR_Player.h"
#include "../DebugHelpers.h"
#include "SFR_PlayerStateBase.generated.h"


class ASFR_PlayerCamera;
class ASFR_Player;
class USFR_InputHandlerComponent;
class USFR_MoveComponent;

UCLASS()
class SKYFLOWER_API USFR_PlayerStateBase : public USFR_StateBase
{
	GENERATED_BODY()

public:
	ASFR_PlayerCamera* CameraRef = nullptr;
	ASFR_Player* PlayerRef = nullptr;
	USFR_InputHandlerComponent* InputHandlerRef = nullptr;
	USFR_MoveComponent* MoveComponent = nullptr;
	//actionComponent

	virtual void OnEnterState()override;
	//virtual void TickState(float DeltaTime)override;
	//virtual void OnExitState()override;

	virtual void ResetSpeedBias() { MoveComponent->ResetSpeedBias(); }
	virtual void ResetGravityBias() { MoveComponent->ResetGravityBias(); }
	virtual void ResetStopPowerBias() { MoveComponent->ResetStopPowerBias(); }
	virtual void ResetAirControlledBias() { MoveComponent->ResetAirControlledBias(); }
	virtual void ResetAirbornTime() { MoveComponent->ResetAirbornTime(); }
};
