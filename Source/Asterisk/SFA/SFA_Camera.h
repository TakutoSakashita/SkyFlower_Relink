// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "SFA_Camera.generated.h"

class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UTimelineComponent;




UCLASS()
class ASTERISK_API ASFA_Camera : public APawn
{
	GENERATED_BODY()

public:
	ASFA_Camera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UArrowComponent* Arrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

private:
	AActor* FollowTarget;

	//BEGIN Aiming
#pragma region Aiming
public:
	bool IsAiming = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* Timeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeLineLength = 0.15f;
	float CurrentTimelinePosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* FloatCurve;

	FOnTimelineFloat InterpFunction{};

	UFUNCTION()
	void AimingProcess(float Value);
	UFUNCTION(BlueprintCallable)
	void StartAim();
	UFUNCTION(BlueprintCallable)
	void EndAim();

	UPROPERTY(BlueprintReadWrite)
	float InitialSpringArmLength = 400.f;
	UPROPERTY(BlueprintReadWrite)
	float InitialFOV = 90.f;
	UPROPERTY(BlueprintReadWrite)
	FVector InitialCameraOffset = FVector(0.f, 0.f, 80.f);

	UPROPERTY(BlueprintReadWrite)
	float AimSpringArmLength = 300.f;
	UPROPERTY(BlueprintReadWrite)
	float AimFOV = 70.f;
	UPROPERTY(BlueprintReadWrite)
	FVector AimCameraOffset = FVector(30.f, 80.f, 70.f);
#pragma endregion
	//END Aiming
public:
	void SetFollowTarget(AActor* Target) { FollowTarget = Target; }

	void Turn(float value);
	void LookUp(float value);

private:
	void UpdateLocation();

};
