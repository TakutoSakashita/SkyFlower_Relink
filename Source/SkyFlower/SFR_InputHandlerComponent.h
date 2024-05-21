// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SFR_InputHandlerComponent.generated.h"

class USFR_MoveComponent;
class USFR_ActionComponent;

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

	///////////////// custom parameter
private:
	UPROPERTY()
	USFR_MoveComponent* MoveComponent;

	UPROPERTY()
	USFR_ActionComponent* ActionComponent;

};
