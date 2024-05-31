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

	///////////////// custom parameter
public:


private:
	//~Parameters for components
	ASFA_Camera* Camera;
	ASFA_Player* Player;
	USFA_InputHandlerComponent* InputHandler;
	USFA_PlayerMovementComponent* PlayerMovementComponent;
	//~End of Parameters for components

};
