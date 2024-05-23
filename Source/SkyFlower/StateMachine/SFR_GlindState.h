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

	virtual void OnEnterState()override;
	virtual void TickState(float DeltaTime)override;
	//virtual void OnExitState()override;
};
