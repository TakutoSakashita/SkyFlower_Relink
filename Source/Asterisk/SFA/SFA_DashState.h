// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_DashState.generated.h"

/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_DashState : public USFA_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Dash_Montage;

	//~BEGIN Dash
	float DashDistance = 2000.f;
	float DashElapsedTime = 0.f;
	float DashTime = 0.8f;
	//bool bIsDashing = true;
	FVector DashDirection = FVector::Zero();
	//~END Dash
};
