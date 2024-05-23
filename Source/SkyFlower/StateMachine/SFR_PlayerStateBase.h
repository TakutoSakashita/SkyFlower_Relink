// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFR_StateBase.h"
#include "../SFR_MoveComponent.h"
#include "../SFR_ActionComponent.h"
#include "../SFR_PlayerController.h"
#include "../SFR_PlayerCamera.h"
#include "../SFR_Player.h"
#include "../DebugHelpers.h"
#include "SFR_PlayerStateBase.generated.h"


class ASFR_PlayerCamera;
class ASFR_Player;
class USFR_InputHandlerComponent;
class USFR_MoveComponent;

UCLASS()
class SKYFLOWER_API USFR_PlayerStateBase : public USFR_StateBase
{
	GENERATED_BODY()

public:
	ASFR_PlayerCamera* CameraRef = nullptr;
	ASFR_Player* PlayerRef = nullptr;
	USFR_InputHandlerComponent* InputHandlerRef = nullptr;
	USFR_MoveComponent* MoveComponent = nullptr;
	//actionComponent

	virtual void OnEnterState()override;
	//virtual void TickState(float DeltaTime)override;
	//virtual void OnExitState()override;


	/* tick */
	virtual void UpdateRootMotion(float DeltaTime); //todo
	virtual void UpdateMove(float DeltaTime);
	virtual void UpdateForce(float DeltaTime); //todo
	virtual void UpdateFly(float DeltaTime); //todo
	virtual void UpdateGravity(float DeltaTime); //todo
	virtual void UpdateRotation(float DeltaTime); //todo

	virtual bool SweepMove(FVector MoveVector, float MoveSpeed);
	virtual FVector GetAlongWallVector(FVector_NetQuantizeNormal HitNormal, FVector MoveVector);

	/* exit */
	float moveSpeed = 100.f;
	float gravity = 5.f;
	float stopPower = 0.01f;
	float airControll = 0.02f;
	float friction = 7.f;
	float rotationSpeed = 15.f;

	float moveSpeedBias = 1.f;
	float gravityBias = 1.f;
	float stopPowerBias = 1.f;
	float airControllBias = 1.f;
	float airborneTime = 0.f;

	virtual void ResetSpeedBias() { moveSpeedBias = 1.f; }
	virtual void ResetGravityBias() { gravityBias = 1.f; }
	virtual void ResetStopPowerBias() { stopPowerBias = 1.f; }
	virtual void ResetAirControlledBias() { airControllBias = 1.f; }
	virtual void ResetAirbornTime() { airborneTime = 0.f; }

};
