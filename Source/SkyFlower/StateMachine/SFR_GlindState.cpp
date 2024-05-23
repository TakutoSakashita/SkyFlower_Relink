// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_GlindState.h"
#include "../DebugHelpers.h"

void USFR_GlindState::OnEnterState()
{
	Super::OnEnterState();
}

void USFR_GlindState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_GlindState::TickState", 100003);
}
