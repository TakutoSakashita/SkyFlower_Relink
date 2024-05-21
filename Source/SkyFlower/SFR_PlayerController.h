// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SFR_PlayerController.generated.h"

class ASFR_PlayerCamera;

UCLASS()
class SKYFLOWER_API ASFR_PlayerController : public APlayerController
{
	GENERATED_BODY()


	///////////////// override function
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	///////////////// custom function
protected:
	void Turn(float Rate);
	void LookUp(float Rate);

	///////////////// custom parameter
private:
	ASFR_PlayerCamera* CameraActor;


};
