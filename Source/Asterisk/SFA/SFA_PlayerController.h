// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SFA_PlayerController.generated.h"

class ASFA_Camera;

UCLASS()
class ASTERISK_API ASFA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

private:
	ASFA_Camera* Camera;

public:
	ASFA_Camera* GetCamera() const { return Camera; }
};
