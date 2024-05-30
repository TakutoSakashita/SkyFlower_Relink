// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_FloatState.generated.h"

/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_FloatState : public USFA_PlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float testParameter = 0.f;

};
