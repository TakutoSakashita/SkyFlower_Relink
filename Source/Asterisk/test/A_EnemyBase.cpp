// Fill out your copyright notice in the Description page of Project Settings.


#include "A_EnemyBase.h"
#include "A_GameMode.h"
#include "A_Player.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetSystemLibrary.h"
#include "../DebugHelpers.h"

AA_EnemyBase::AA_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AA_EnemyBase::BeginPlay()
{
}

void AA_EnemyBase::Tick(float DeltaTime)
{
}

/// @brief €–SI—¹ˆ—
void AA_EnemyBase::OnEndDead()
{
	Destroy();
}

void AA_EnemyBase::GetDamage(int32 damage)
{
	Debug::PrintFixedLine("GetDamage EnemyBase");
}

/////////////////////////////FORCEINLINE
AA_GameMode* AA_EnemyBase::GetGameMode() const
{
	return Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

AA_Player* AA_EnemyBase::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}