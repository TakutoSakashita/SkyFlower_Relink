// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SFR_PlayerController.generated.h"

class ASFR_Camera;

UCLASS()
class ASTERISK_API ASFR_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	///////////////// override function
protected:
	virtual void BeginPlay() override;

	///////////////// custom function


	///////////////// custom parameter
private:
	ASFR_Camera* Camera;

	///////////////// GET
public:
	ASFR_Camera* GetCamera() const { return Camera; }
};
