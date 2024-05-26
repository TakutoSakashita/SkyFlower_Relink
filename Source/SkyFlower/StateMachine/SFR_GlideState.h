// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_PlayerStateBase.h"
#include "SFR_GlideState.generated.h"

/**
 *
 */
UCLASS()
class SKYFLOWER_API USFR_GlideState : public USFR_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState()override;
	virtual void TickState(float DeltaTime)override;
	virtual void OnExitState()override;

	/* enter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float glideSpeedBias = 1.7f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float glideGravityBias = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float glideStopPowerBias = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float glideAirControllBias = 1.5f;

	virtual void SetGlideSpeedBias() { MoveComponent->moveSpeedBias = glideSpeedBias; }
	virtual void SetGlideGravityBias() { MoveComponent->gravityBias = glideGravityBias; }
	virtual void SetGlideStopPowerBias() { MoveComponent->stopPowerBias = glideStopPowerBias; }
	virtual void SetGlideAirControlledBias() { MoveComponent->airControllBias = glideAirControllBias; }

};
