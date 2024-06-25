// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_GameMode.h"
#include "SFA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SFA_DestructibleObject.h"
#include "SFA_HUD.h"

ASFA_GameMode::ASFA_GameMode()
{
	PlayerControllerClass = ASFA_PlayerController::StaticClass();
	HUDClass = ASFA_HUD::StaticClass();
}

void ASFA_GameMode::StartPlay()
{
	Super::StartPlay();

	// 破壊可能オブジェクトの初期化
	DestroyedObjectCount = 0;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFA_DestructibleObject::StaticClass(), MaxDestroyedObjectCount);
}

void ASFA_GameMode::ObjectDestroyed()
{
	DestroyedObjectCount++;

	if (DestroyedObjectCount >= MaxDestroyedObjectCount.Num())
	{
		OnObjectDestroyed.Broadcast();
	}
}
