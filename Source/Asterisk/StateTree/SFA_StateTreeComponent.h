// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "SFA_StateTreeComponent.generated.h"

/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_StateTreeComponent : public UStateTreeComponent
{
	GENERATED_BODY()
	
public:
	USFA_StateTreeComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SwitchStateTree(UStateTree* const InStateTree);
};