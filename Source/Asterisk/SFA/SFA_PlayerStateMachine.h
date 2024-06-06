// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../StateMachine/SFR_StateMachineComponent.h"
#include "SFA_PlayerStateMachine.generated.h"

class ASFA_Camera;
class ASFA_Player;
class USFA_InputHandlerComponent;
class USFA_PlayerMovementComponent;


UCLASS()
class ASTERISK_API USFA_PlayerStateMachine : public USFR_StateMachineComponent
{
	GENERATED_BODY()

public:
	USFA_PlayerStateMachine();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeStates() override;

	/////////////////// custom function
public:
	//todo functions for states











private:
	void InitializePointers();
	void UpdateForceMove(float DeltaTime);

	///////////////// custom parameter
public:


private:
	//~BEGIN components
	ASFA_Camera* Camera;
	ASFA_Player* Player;
	USFA_InputHandlerComponent* InputHandler;
	USFA_PlayerMovementComponent* PlayerMovementComponent;
	//~END components

	//~BEGIN Dash
	float DashDistance = 2000.f;
	float DashElapsedTime = 0.f;
	float DashTime = 0.8f;
	bool bIsDashing = false;
	FVector DashDirection = FVector::Zero();
	//~END Dash

public:
	void SetDashDistance(float distance) { DashDistance = distance; }
	void SetDashElapsedTime(float distance) { DashElapsedTime = distance; }
	void SetDashTime(float time) { DashTime = time; }
	void SetIsDashing(bool isDashing) { bIsDashing = isDashing; }
	bool GetIsDashing()const { return bIsDashing; }
	void SetDashDirection(FVector direction) { DashDirection = direction; }
};
