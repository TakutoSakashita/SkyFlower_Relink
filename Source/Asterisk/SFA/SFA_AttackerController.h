// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_EnemyControllerBace.h"
#include "SFA_AttackerController.generated.h"

class ASFA_Attacker;

UCLASS()
class ASTERISK_API ASFA_AttackerController : public ASFA_EnemyControllerBace
{
	GENERATED_BODY()

public:
	ASFA_AttackerController();

	////////////////////////////////////////////////// Override
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void UpdateOnNormal(const float InDeltaTime) override;
	virtual void OnBeginAttack() override;
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) override;
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) override;
	virtual void OnEndAttack() override;
	virtual void OnBeginDead() override;
	virtual void UpdateOnDead(const float InDeltaTime) override;
	virtual void OnEndDead() override;

	////////////////////////////////////////////////// Custom
private:
	UPROPERTY()
	ASFA_Attacker* OwnerAttacker;
};
