// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFR_Player.generated.h"

class USFR_InputHandlerComponent;

UCLASS()
class SKYFLOWER_API ASFR_Player : public APawn
{
	GENERATED_BODY()

	///////////////// override function
public:
	ASFR_Player();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom parameter
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USFR_InputHandlerComponent* InputComp;
};
