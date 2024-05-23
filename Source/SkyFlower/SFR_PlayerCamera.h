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



private:
	AActor* FollowTarget;
};
