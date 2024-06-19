// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SFA_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectDestroyed);

UCLASS()
class ASTERISK_API ASFA_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASFA_GameMode();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnObjectDestroyed OnObjectDestroyed;

	void ObjectDestroyed();

	UPROPERTY(EditAnywhere)
	int32 MaxDestroyedObjectCount = 4;
	
private:
	int32 DestroyedObjectCount;
};
