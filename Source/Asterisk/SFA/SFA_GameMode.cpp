// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_GameMode.h"
#include "SFA_PlayerController.h"
#include "SFA_HUD.h"

ASFA_GameMode::ASFA_GameMode()
{
	PlayerControllerClass = ASFA_PlayerController::StaticClass();
	HUDClass = ASFA_HUD::StaticClass();

	DestroyedObjectCount = 0;
}

void ASFA_GameMode::ObjectDestroyed()
{
	DestroyedObjectCount++;
	if (DestroyedObjectCount >= MaxDestroyedObjectCount)
	{
		OnObjectDestroyed.Broadcast();
	}
}
