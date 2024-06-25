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

	virtual void StartPlay() override;

	// 破壊可能オブジェクトのデリゲート
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnObjectDestroyed OnObjectDestroyed;
	UPROPERTY()
	TArray<AActor*> MaxDestroyedObjectCount;
	UFUNCTION()
	void ObjectDestroyed();

	
private:
	int32 DestroyedObjectCount;
};
