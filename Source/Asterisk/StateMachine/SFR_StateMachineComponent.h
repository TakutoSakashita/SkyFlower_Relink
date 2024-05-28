// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SFR_StateMachineComponent.generated.h"

class USFR_StateBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTERISK_API USFR_StateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

	///////////////// override function
public:
	USFR_StateMachineComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom function
public:
	virtual void SwitchStateByKey(FString StateKey);

	virtual void InitStateManager();

protected:
	virtual void InitializeStates();

	///////////////// custom parameter
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine")
	TMap<FString, TSubclassOf<USFR_StateBase>> AvailableStates;

	UPROPERTY()
	TMap<FString, USFR_StateBase*> StateMap;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine")
	FString InitialState;

	UPROPERTY(BlueprintReadOnly)
	USFR_StateBase* CurrentState = nullptr;

	bool bCanTickState = true;

		
};
