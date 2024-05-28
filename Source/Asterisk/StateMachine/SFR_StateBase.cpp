// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_StateBase.h"
#include "../DebugHelpers.h"

#define LOG_PRINT 0
#define DEBUG_FIXED(text,num) if(LOG_PRINT) Debug::PrintFixedLine(text, num)
#define DEBUG_PRINT(text) if(LOG_PRINT) Debug::Print(text)

void USFR_StateBase::OnEnterState()
{
	DEBUG_PRINT("USFR_StateBase::OnEnterState");
}

void USFR_StateBase::TickState(float DeltaTime)
{
	DEBUG_FIXED("USFR_StateBase::TickState", 10001);
}

void USFR_StateBase::OnExitState()
{
	DEBUG_PRINT("USFR_StateBase::OnExitState");
}
