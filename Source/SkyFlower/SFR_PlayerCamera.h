// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFR_PlayerCamera.generated.h"

UCLASS()
class SKYFLOWER_API ASFR_PlayerCamera : public AActor
{
	GENERATED_BODY()

	///////////////// override function
public:
	ASFR_PlayerCamera();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom function

	///////////////// custom parameter
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmMain;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraMain;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UArrowComponent* CameraArrowMain;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//class USpringArmComponent* SpringArmLeft;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//class UCameraComponent* CameraLeft;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//class UArrowComponent* CameraArrowLeft;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//class USpringArmComponent* SpringArmRight;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//class UCameraComponent* CameraRight;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//class UArrowComponent* CameraArrowRight;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetFollowTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	UCameraComponent* GetMainCamera() const { return CameraMain; }

private:
	AActor* FollowTarget;
};
