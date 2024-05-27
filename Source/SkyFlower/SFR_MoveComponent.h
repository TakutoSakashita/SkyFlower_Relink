// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachine/SFR_StateMachineComponent.h"
#include "SFR_MoveComponent.generated.h"



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
class USFR_InputHandlerComponent;
class ASFR_Player;
class ASFR_PlayerCamera;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYFLOWER_API USFR_MoveComponent : public USFR_StateMachineComponent
{
	GENERATED_BODY()

	///////////////// override function
public:
	USFR_MoveComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void SwitchStateByKey(FString StateKey) override;

	virtual void InitStateManager() override;

protected:
	virtual void InitializeStates() override;

	///////////////// custom function

public:
	void Initialize(ASFR_Player* player);

	//void MoveForward(float Value);
	//void MoveRight(float Value);


	///////////////// custom parameter
public:
	USFR_InputHandlerComponent* InputHandler = nullptr;
	ASFR_Player* PlayerRef = nullptr;
	ASFR_PlayerCamera* CameraRef = nullptr;

	float CurrentVelocity = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugLog = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovementState MoveState = EMovementState::Float;


	void AddForwardMovementInput(float InputValue);
	void AddRightMovementInput(float InputValue);

	/* tick */
	virtual void UpdateRootMotion(float DeltaTime); //todo
	virtual void UpdateMove(float DeltaTime); //todo
	//virtual void UpdateGravity(float DeltaTime);//todo

	virtual void UpdateForce(float DeltaTime);
	//virtual void UpdateFly(float DeltaTime);
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
	//bool bFloat = false;
	//bool bWire = false;
	bool bForce = false;
	//bool bFly = false;
	bool bGlide = false;
	//bool bDive = false;

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

	//float currentFlyVelocityValue;
	//float flyDurationTimer;
	//FVector flyVec;

	//float flyVelocityValue = 5.f;
	//float flyZVelocity = 10.f;
	//float flyDuration = 3.f;
	//UCurveFloat* flyCurveZ;
	//UCurveFloat* flyCurveSpeed;

	//FVector wireMoveVector;
	//float wireMoveSpeed;
	//float wireMoveTime;
	//float currentWireMoveTime;

	//FVector2D beforeMoveVector;
	//FVector beforePos;

	//float diveSpeedBias = 3.5f;
	//float diveGravity = 20.f;
	//float diveThreshold = 5.f;
	//void SetDiveSpeedBias() { moveSpeedBias = diveSpeedBias; }

	//float graidSpeedBias = 1.7f;
	//float graidGravityBias = 0.2f;
	//float graidStopPowerBias = 1.5f;
	//float graidAirControllBias = 1.5f;

	//float airDashSpeed = 20.f;
	//float airDashDeceleration = 14.f;
	
	//float airJumpPower = 20.f;
	//float airJumpDeceleration = 14.f;
};
