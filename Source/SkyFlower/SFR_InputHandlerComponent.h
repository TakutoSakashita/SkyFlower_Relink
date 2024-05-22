// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SFR_InputHandlerComponent.generated.h"


UENUM(BlueprintType)
enum class EInputState : uint8
{
	None,
	
	Both_enable,
	Move_enable,
	Action_enable,
	Both_disable,
	
	ElementsNum,
};


// forward declaration
class USFR_MoveComponent;
class USFR_ActionComponent;
class ASFR_PlayerCamera;
class ASFR_Player;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYFLOWER_API USFR_InputHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

	///////////////// override function
public:
	USFR_InputHandlerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom function
public:
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void Initialize(AActor* player);

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);


	///////////////// custom parameter
public:
	UPROPERTY()
	USFR_MoveComponent* MoveComponent;

	UPROPERTY()
	USFR_ActionComponent* ActionComponent;

	UPROPERTY()
	ASFR_Player* Player;

	UPROPERTY()
	ASFR_PlayerCamera* Camera;

};
