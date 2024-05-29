// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_GameMode.h"
#include "SFA_PlayerController.h"

ASFA_GameMode::ASFA_GameMode()
{
	PlayerControllerClass = ASFA_PlayerController::StaticClass();
}
