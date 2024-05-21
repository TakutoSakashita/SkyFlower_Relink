// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_GameMode.h"
#include "SFR_PlayerController.h"

ASFR_GameMode::ASFR_GameMode()
{
	PlayerControllerClass = ASFR_PlayerController::StaticClass();
}
