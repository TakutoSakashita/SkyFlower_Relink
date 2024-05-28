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
class USFR_InputHandlerComponent;
class ASFR_PlayerCamera;
class ASFR_Player;

UCLASS()
class ASTERISK_API USFR_PlayerStateMachine : public USFR_StateMachineComponent
{
	GENERATED_BODY()
	
};
