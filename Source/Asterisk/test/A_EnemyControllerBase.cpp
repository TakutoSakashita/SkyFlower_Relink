// Fill out your copyright notice in the Description page of Project Settings.


#include "A_EnemyControllerBase.h"
#include "A_GameMode.h"
#include "A_Player.h"
#include <Kismet/GameplayStatics.h>


AA_EnemyControllerBase::AA_EnemyControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AA_EnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AA_EnemyControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AA_EnemyControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AA_GameMode* AA_EnemyControllerBase::GetGameMode() const
{
	return Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

AA_Player* AA_EnemyControllerBase::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}
