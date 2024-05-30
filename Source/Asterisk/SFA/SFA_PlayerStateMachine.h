// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../StateMachine/SFR_StateMachineComponent.h"
#include "SFA_PlayerStateMachine.generated.h"

class ASFA_Camera;
class ASFA_Player;
class USFA_InputHandlerComponent;
class USFA_PlayerMovementComponent;

UENUM(BlueprintType)
enum class ESFA_MoveState : uint8
{
	None,

	Glide,	// move in air
	Walk,	// move on land
	Dash,	// jump or dash in air
	
	Land,	// idle on land
	Jump,	// jump on land
	Float,	// idle in air
	
	Dive,	// 
	Fall,	// 

	ElementsNum,
};

enum class ESFA_AttackState : uint8
{
	None,

	NormalAttack,	// normal 1
	HomingAttack,
	LaserAttack,

	ElementsNum,
};

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

	///////////////// custom parameter
public:
	ESFA_MoveState MoveState = ESFA_MoveState::Float;
	ESFA_AttackState AttackState = ESFA_AttackState::None;

private:
	//~Parameters for components
	ASFA_Camera* Camera;
	ASFA_Player* Player;
	USFA_InputHandlerComponent* InputHandler;
	USFA_PlayerMovementComponent* PlayerMovementComponent;
	//~End of Parameters for components

};
