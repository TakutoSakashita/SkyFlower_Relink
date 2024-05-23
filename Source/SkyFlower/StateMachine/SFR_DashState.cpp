// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_DashState.h"
#include "../DebugHelpers.h"

void USFR_DashState::OnEnterState()
{
	Super::OnEnterState();
}

void USFR_DashState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	Debug::PrintFixedLine("USFR_DashState::TickState", 100002);
}
