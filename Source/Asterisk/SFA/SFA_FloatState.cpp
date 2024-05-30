// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_FloatState.h"

//debug
#include "../DebugHelpers.h"
#define LOG_PRINT 1
#define DEBUG_PRINT(text) if(LOG_PRINT) Debug::Print(text);
#define DEBUG_FIXED(text,num) if(LOG_PRINT) Debug::PrintFixedLine(text, num);


void USFA_FloatState::OnEnterState()
{
	Super::OnEnterState();

	DEBUG_PRINT("USFA_FloatState::OnEnterState()")
}

void USFA_FloatState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	DEBUG_FIXED("USFA_FloatState::TickState", 1000000)

}

void USFA_FloatState::OnExitState()
{
	Super::OnExitState();
	DEBUG_PRINT("USFA_FloatState::OnExitState()")

}
