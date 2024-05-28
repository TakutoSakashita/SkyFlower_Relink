// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFR_Camera.generated.h"

UCLASS()
class ASTERISK_API ASFR_Camera : public APawn
{
	GENERATED_BODY()


	///////////////// override function
public:
	ASFR_Camera();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;



	///////////////// custom parameter
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmMain;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraMain;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UArrowComponent* CameraArrowMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebugLog = false;

	///////////////// custom function
public:
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetFollowTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	UCameraComponent* GetMainCamera() const { return CameraMain; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void Turn(float value);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void LookUp(float value);


	float deadZone = 0.05f;
	float pitch_sensitivity = 2.f;
	float yaw_sensitivity = 2.f;

	float default_pitch_min = -40.f;
	float current_pitch_min = -40.f;
	//float dive_pitch_min = -40.f;

	float default_pitch_max = 65.f;
	float current_pitch_max = 65.f;
	//float dive_pitch_max = 30.f;

	float default_boom_length_max = 500.f;
	float current_boom_length_max = 500.f;
	//float dive_boom_length_max = 400.f;
	//float fly_boom_length_max = 480.f;

	float default_boom_length_min = 180.f;


	void SetBoomLength(float boomLength) { current_boom_length_max = boomLength; }
	//void SetFlyBoomLength() { current_boom_length_max = fly_boom_length_max; }
	//void SetDiveBoomLength() { current_boom_length_max = dive_boom_length_max; }
	//void SetDivePitch() { current_pitch_min = dive_pitch_min; current_pitch_max = dive_pitch_max; }

	void ResetBoomLength() { current_boom_length_max = default_boom_length_max; }
	void ResetPitch() {
		current_pitch_min = default_pitch_min;
		current_pitch_max = default_pitch_max;
	}

private:
	AActor* FollowTarget;

	FVector2D inputValue;
};
