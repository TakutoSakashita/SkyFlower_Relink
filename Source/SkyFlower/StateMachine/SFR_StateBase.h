// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SFR_StateBase.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class SKYFLOWER_API USFR_StateBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanTickState = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanRepeat = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName StateDisplayName;


	virtual void OnEnterState();
	virtual void TickState(float DeltaTime);
	virtual void OnExitState();
};
