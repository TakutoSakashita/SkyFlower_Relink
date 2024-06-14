// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_StunState.generated.h"

/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_StunState : public USFA_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;
};
