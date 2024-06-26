// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_JumpState.generated.h"

/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_JumpState : public USFA_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AirJump_Montage;

	//~BEGIN Dash
	float AirJumpDistance = 2000.f;
	float AirJumpElapsedTime = 0.f;
	float AirJumpTime = 0.8f;
	//bool bIsAirJumping = true;
	FVector AirJumpDirection = FVector::UnitZ();
	//~END Dash
	
};
