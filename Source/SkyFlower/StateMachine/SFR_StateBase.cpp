// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_StateBase.h"
#include "../DebugHelpers.h"

//#undef DEBUG_LOG_ENABLE

void USFR_StateBase::OnEnterState()
{
	Debug::Print("USFR_StateBase::OnEnterState");
}

void USFR_StateBase::TickState(float DeltaTime)
{
	Debug::PrintFixedLine("USFR_StateBase::TickState",10001);
}

void USFR_StateBase::OnExitState()
{
	Debug::Print("USFR_StateBase::OnExitState");
}
