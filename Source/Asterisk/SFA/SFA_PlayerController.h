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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASFA_Camera> CameraClass;

private:
	ASFA_Camera* Camera;

public:
	UFUNCTION(BlueprintCallable)
	ASFA_Camera* GetCamera() const { return Camera; }
};
