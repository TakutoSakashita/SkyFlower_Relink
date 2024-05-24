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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidSpeedBias = 1.7f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidGravityBias = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidStopPowerBias = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidAirControllBias = 1.5f;

	virtual void SetGraidSpeedBias() { MoveComponent->moveSpeedBias = graidSpeedBias; }
	virtual void SetGraidGravityBias() { MoveComponent->gravityBias = graidGravityBias; }
	virtual void SetGraidStopPowerBias() { MoveComponent->stopPowerBias = graidStopPowerBias; }
	virtual void SetGraidAirControlledBias() { MoveComponent->airControllBias = graidAirControllBias; }
};
