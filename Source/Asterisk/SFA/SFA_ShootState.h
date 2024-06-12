// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_ShootState.generated.h"

/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_ShootState : public USFA_PlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;

public:
	//~BEGIN Shoot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UAnimMontage* ShootMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<ASFA_Bullet> BulletClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UParticleSystem* ShootEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	USoundBase* ShootSound;
	//~END Shoot
};
