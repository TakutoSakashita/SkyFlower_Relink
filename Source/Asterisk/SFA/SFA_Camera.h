// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFA_Camera.generated.h"

class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;




UCLASS()
class ASTERISK_API ASFA_Camera : public APawn
{
	GENERATED_BODY()

public:
	ASFA_Camera();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom parameter
public:
	UArrowComponent* CameraArrowMain;
	USpringArmComponent* SpringArmMain;
	UCameraComponent* CameraMain;

private:
	AActor* FollowTarget;

	///////////////// custom function
public:
	void SetFollowTarget(AActor* Target) { FollowTarget = Target; }

	void Turn(float value);
	void LookUp(float value);

private:
	void UpdateLocation();

};
