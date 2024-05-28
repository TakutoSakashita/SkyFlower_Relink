// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_PlayerStateBase.h"
#include "SFR_DashState.generated.h"

/**
 *
 */
UCLASS()
class ASTERISK_API USFR_DashState : public USFR_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState()override;
	virtual void TickState(float DeltaTime)override;
	//virtual void OnExitState()override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airDashSpeed = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airDashDeceleration = 14.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airJumpPower = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airJumpDeceleration = 14.f;
};
