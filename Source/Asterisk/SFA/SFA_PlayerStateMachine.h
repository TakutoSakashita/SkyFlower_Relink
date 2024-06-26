// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../StateMachine/SFR_StateMachineComponent.h"
#include "SFA_PlayerStateMachine.generated.h"

class ASFA_Bullet;
struct FInputActionValue;
class ASFA_Camera;
class ASFA_Player;
class USFA_InputHandlerComponent;
class USFA_PlayerMovementComponent;
class UAnimMontage;

UCLASS()
class ASTERISK_API USFA_PlayerStateMachine : public USFR_StateMachineComponent
{
	GENERATED_BODY()

public:
	USFA_PlayerStateMachine();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeStates() override;

	/////////////////// custom function
public:
	void Move(const FInputActionValue& Value) const;
	void Look(const FInputActionValue& Value) const;

private:
	void InitializePointers();
	void UpdateForceMove(float DeltaTime);

	///////////////// custom parameter
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAiming = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsBoosting = false;

private:
	//~BEGIN components
	UPROPERTY()
	ASFA_Camera* Camera = nullptr;
	UPROPERTY()
	ASFA_Player* Player = nullptr;
	UPROPERTY()
	USFA_InputHandlerComponent* InputHandler = nullptr;
	UPROPERTY()
	USFA_PlayerMovementComponent* PlayerMovementComponent = nullptr;
	//~END components

	//~BEGIN Dash
	float DashDistance = 2000.f;
	float DashElapsedTime = 0.f;
	float DashTime = 0.8f;
	bool bIsDashing = false;
	FVector DashDirection = FVector::Zero();
	//~END Dash

	///////////////// get set
public:
	void SetDashDistance(const float Distance) { DashDistance = Distance; }
	void SetDashElapsedTime(const float Distance) { DashElapsedTime = Distance; }
	void SetDashTime(const float Time) { DashTime = Time; }
	void SetIsDashing(const bool IsDashing) { bIsDashing = IsDashing; }
	bool GetIsDashing() const { return bIsDashing; }
	void SetDashDirection(const FVector& Direction) { DashDirection = Direction; }
};
