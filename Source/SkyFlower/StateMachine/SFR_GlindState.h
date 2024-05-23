// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_PlayerStateBase.h"
#include "SFR_GlindState.generated.h"

/**
 * 
 */
UCLASS()
class SKYFLOWER_API USFR_GlindState : public USFR_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState()override;
	virtual void TickState(float DeltaTime)override;
	virtual void OnExitState()override;

	/* enter */
	float graidSpeedBias = 1.7f;
	float graidGravityBias = 0.2f;
	float graidStopPowerBias = 1.5f;
	float graidAirControllBias = 1.5f;

	virtual void SetGraidSpeedBias() { moveSpeedBias = graidSpeedBias; }
	virtual void SetGraidGravityBias() { gravityBias = graidGravityBias; }
	virtual void SetGraidStopPowerBias() { stopPowerBias = graidStopPowerBias; }
	virtual void SetGraidAirControlledBias() { airControllBias = graidAirControllBias; }
};
