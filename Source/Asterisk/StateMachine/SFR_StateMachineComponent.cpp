// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_StateMachineComponent.h"
#include "SFR_StateBase.h"
#include "../DebugHelpers.h"

USFR_StateMachineComponent::USFR_StateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USFR_StateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeStates();

	InitStateManager();
}

void USFR_StateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!bCanTickState) return;
	if (!CurrentState) {
		Debug::PrintFixedLine("CurrentState : NULL", 1001);
		return;
	}

	CurrentState->TickState(DeltaTime);

	Debug::PrintFixedLine("CurrentState : " + CurrentState->StateDisplayName.ToString(), 1001);

}

void USFR_StateMachineComponent::SwitchStateByKey(FString StateKey)
{
	USFR_StateBase* NewState = StateMap.FindRef(StateKey);

	// state do not exist
	if (!NewState->IsValidLowLevel()) {
		Debug::Print(StateKey + " STATE IS NOT EXIST");
		return;
	}

	if (!CurrentState)//if is initial state
	{
		CurrentState = NewState; // set initial state
	}
	else if ((CurrentState->GetClass() == NewState->GetClass() && !CurrentState->bCanRepeat))// if is same state class and not repeatable
	{
		Debug::Print(StateKey + " IS NOT REPEATABLE. SWITCH FAILED");
	}
	else// perform state switch
	{
		bCanTickState = false;
		CurrentState->OnExitState();
		CurrentState = NewState;
	}

	// enter new state
	if (CurrentState) {
		CurrentState->OnEnterState();
		bCanTickState = true;
	}

}

void USFR_StateMachineComponent::InitStateManager()
{
	SwitchStateByKey(InitialState);
}

void USFR_StateMachineComponent::InitializeStates()
{
	/*Create State and hold them in memory for when needed*/
	for (auto It = AvailableStates.CreateConstIterator(); It; ++It)
	{
		if (It->Value) {
			USFR_StateBase* State = NewObject<USFR_StateBase>(this, It->Value);
			StateMap.Add(It->Key, State);
		}
		else {
			Debug::Print(It->Key + "NOT FOUND");
		}
	}
}




