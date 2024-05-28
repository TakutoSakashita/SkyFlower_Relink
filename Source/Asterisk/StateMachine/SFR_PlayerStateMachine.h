// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_StateMachineComponent.h"
#include "SFR_PlayerStateMachine.generated.h"


UENUM(BlueprintType)
enum class EMovementState : uint8
{
	None,

	Walk,
	Jump,
	Float,
	Dash, // on land
	Glide, // in air
	Dive, // flying down


	ElementsNum,
};

// forward declaration
class ASFR_Camera;
class ASFR_Player;
class USFR_InputHandlerComponent;

UCLASS()
class ASTERISK_API USFR_PlayerStateMachine : public USFR_StateMachineComponent
{
	GENERATED_BODY()
	

	///////////////// override function
public:
	USFR_PlayerStateMachine();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* derived from parent class */
	//virtual void SwitchStateByKey(FString StateKey) override;
	//virtual void InitStateManager() override;
	//virtual void InitializeStates() override;
	
	/////////////////// custom function

public:
	void Initialize(ASFR_Player* player);


	///////////////// custom parameter
public:
	USFR_InputHandlerComponent* InputHandler = nullptr;
	ASFR_Player* PlayerRef = nullptr;
	ASFR_Camera* CameraRef = nullptr;

	float CurrentVelocity = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugLog = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovementState MoveState = EMovementState::Float;


	void AddForwardMovementInput(float InputValue);
	void AddRightMovementInput(float InputValue);

	/* tick */
	virtual void UpdateRootMotion(float DeltaTime); //todo
	virtual void UpdateMove(float DeltaTime); 
	//virtual void UpdateGravity(float DeltaTime);

	virtual void UpdateForce(float DeltaTime);
	virtual void UpdateRotation(float DeltaTime);

	virtual bool SweepMove(FVector MoveVector, float MoveSpeed);
	virtual FVector GetAlongWallVector(FVector_NetQuantizeNormal HitNormal, FVector MoveVector);
	bool UnderCheck();
	void AddForce(FVector Vector, float Value, float Deceleration);

	/* parameter */

	FVector2D inputValue;
	FVector2D inputBias;
	bool bInputFwd;
	bool bInputRight;

	bool bRootMotion = false;
	bool bForce = false;
	bool bGlide = false;


	float moveSpeed = 20.f;
	float gravity = 5.f;
	float stopPower = 0.01f;
	float airControll = 0.02f;

	float moveSpeedBias = 1.f;
	float gravityBias = 1.f;
	float stopPowerBias = 1.f;
	float airControllBias = 1.f;

	float airborneTime = 0.f;

	float friction = 7.f;
	float rotationSpeed = 15.f;

	virtual void ResetSpeedBias() { moveSpeedBias = 1.f; }
	virtual void ResetGravityBias() { gravityBias = 1.f; }
	virtual void ResetStopPowerBias() { stopPowerBias = 1.f; }
	virtual void ResetAirControlledBias() { airControllBias = 1.f; }
	virtual void ResetAirbornTime() { airborneTime = 0.f; }

	float beforeGravityAcceleration;

	FVector forceVector;
	float forceValue;
	float forceDecelerationValue;
};
