// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_PlayerStateMachine.h"
#include "Kismet/GameplayStatics.h"
#include "SFA_PlayerController.h"
// player components
#include "SFA_Camera.h"
#include "SFA_Player.h"
#include "SFA_PlayerMovementComponent.h"
#include "SFA_InputHandlerComponent.h"
#include "SFA_PlayerStateBase.h"
// enhanced input
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
//debug
#include "../DebugHelpers.h"
#define LOG_PRINT 1
#define DEBUG_PRINT(text) if(LOG_PRINT) Debug::Print(text);
#define DEBUG_FIXED(text,num) if(LOG_PRINT) Debug::PrintFixedLine(text, num);

USFA_PlayerStateMachine::USFA_PlayerStateMachine()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USFA_PlayerStateMachine::BeginPlay()
{
	Super::BeginPlay();
	InitializePointers();
}

void USFA_PlayerStateMachine::InitializeStates()
{
	Super::InitializeStates();
	/*Create State and hold them in memory for when needed*/
	for (auto It = StateMap.CreateConstIterator(); It; ++It)
	{
		USFA_PlayerStateBase* state = Cast<USFA_PlayerStateBase>(It->Value);
		if (IsValid(state))
			state->PlayerStateMachine = this;
		DEBUG_PRINT(state->GetName())
	}
}

void USFA_PlayerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USFA_PlayerStateMachine::InitializePointers()
{
	Camera = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	Player = Cast<ASFA_Player>(GetOwner());
	InputHandler = Player->GetInputHandler();
	PlayerMovementComponent = Player->GetPlayerMovement();
}
