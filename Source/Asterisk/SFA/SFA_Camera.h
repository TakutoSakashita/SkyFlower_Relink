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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialSpringArmLength = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialFOV = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InitialCameraOffset = FVector(0.f, 0.f, 80.f);

#pragma region Aiming
	//~BEGIN Aiming
public:
	bool IsAiming = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* AimTimeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimTimeLineLength = 0.15f;
	float AimCurrentTimelinePosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* AimFloatCurve;

	FOnTimelineFloat AimInterpFunction{};

	UFUNCTION()
	void AimingProcess(float Value);
	UFUNCTION(BlueprintCallable)
	void StartAim();
	UFUNCTION(BlueprintCallable)
	void EndAim();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimSpringArmLength = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimFOV = 70.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AimCameraOffset = FVector(30.f, 80.f, 70.f);
	//~END Aiming
#pragma endregion


#pragma region Boosting
	//~BEGIN Boosting
public:
	bool IsBoosting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* BoostTimeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoostTimeLineLength = 0.15f;
	float BoostCurrentTimelinePosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* BoostFloatCurve;

	FOnTimelineFloat BoostInterpFunction{};

	UFUNCTION()
	void BoostingProcess(float Value);
	UFUNCTION(BlueprintCallable)
	void StartBoost();
	UFUNCTION(BlueprintCallable)
	void EndBoost();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoostSpringArmLength = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoostFOV = 120.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoostCameraOffset = FVector(0.f, 0.f, 50.f);

	
	//~ENd Boosting
#pragma endregion

public:
	void SetFollowTarget(AActor* Target) { FollowTarget = Target; }
	void Turn(float value);
	void LookUp(float value);
	FVector GetCameraCompForwardVector() const;
	FVector GetCameraCompLocation() const;

private:
	void UpdateLocation();
};
