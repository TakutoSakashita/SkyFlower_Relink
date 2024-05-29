// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SFR_InputHandlerComponent.generated.h"


UENUM(BlueprintType)
enum class ESFR_InputState : uint8
{
	None,

	Both_enable,
	Move_disable,
	//Action_disable,
	//Both_disable,

	ElementsNum,
};


// forward declaration
class ASFR_Camera;
class ASFR_Player;
class USFR_PlayerStateMachine;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTERISK_API USFR_InputHandlerComponent : public UActorComponent
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
	void Initialize(AActor* player);
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	UFUNCTION(BlueprintCallable)
	void Key_E_Pressed();

	UFUNCTION(BlueprintCallable)
	void Key_E_Released();



	///////////////// custom parameter
public:
	UPROPERTY()
	ESFR_InputState InputState = ESFR_InputState::Both_enable;

	UPROPERTY()
	ASFR_Camera* Camera;

	UPROPERTY()
	ASFR_Player* Player;

	UPROPERTY()
	USFR_PlayerStateMachine* PlayerStateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebugLog = false;

};
