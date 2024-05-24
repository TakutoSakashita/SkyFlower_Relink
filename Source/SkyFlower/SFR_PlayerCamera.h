// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFR_PlayerCamera.generated.h"

UCLASS()
class SKYFLOWER_API ASFR_PlayerCamera : public APawn
{
	GENERATED_BODY()

	///////////////// override function
public:
	ASFR_PlayerCamera();
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

	float pitch_min = -40.f;
	float current_pitch_min = -40.f;
	float dive_pitch_min = -40.f;

	float pitch_max = 65.f;
	float current_pitch_max = 65.f;
	float dive_pitch_max = 30.f;

	float boom_length_min = 180.f;

	float current_boom_length_max = 500.f;
	float boom_length_max = 500.f;
	float dive_boom_length_max = 400.f;
	float graid_boom_length_max = 520.f;
	float fly_boom_length_max = 480.f;


	void SetDiveBoomLength() { current_boom_length_max = dive_boom_length_max; }
	void SetDivePitch() { current_pitch_min = dive_pitch_min; current_pitch_max = dive_pitch_max; }

	void SetGraidBoomLength() { current_boom_length_max = graid_boom_length_max; }
	void SetFlyBoomLength() { current_boom_length_max = fly_boom_length_max; }

	void ResetBoomLength() { current_boom_length_max = boom_length_max; }
	void ResetPitch() { current_pitch_min = pitch_min; current_pitch_max = pitch_max; }

private:
	AActor* FollowTarget;

	FVector2D inputValue;
};
