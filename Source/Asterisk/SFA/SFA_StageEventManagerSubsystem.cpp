// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_StageEventManagerSubsystem.h"

bool USFA_StageEventManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// return Super::ShouldCreateSubsystem(Outer);

	return true;
}

void USFA_StageEventManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, TEXT("UNpcManager::Initialize()"));
	}
}

void USFA_StageEventManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, TEXT("USFA_StageEventManagerSubsystem::Deinitialize()"));
	}
}

void USFA_StageEventManagerSubsystem::OnBeginEvent()
{
	OnBeginEventDispatcher.Broadcast();
}

void USFA_StageEventManagerSubsystem::OnEndEvent()
{
	OnEndEventDispatcher.Broadcast();
}
