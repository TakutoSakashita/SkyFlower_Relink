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
	void Initialize(ASFR_Player* player, USFR_InputHandlerComponent* inputHandler);

	void MoveForward(float Value);
	void MoveRight(float Value);

	///////////////// custom parameter
public:
	USFR_InputHandlerComponent* InputHandler = nullptr;
	ASFR_Player* PlayerRef = nullptr;
	ASFR_PlayerCamera* CameraRef = nullptr;

	float CurrentVelocity = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebugLog = false;
};
