// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_EnemyBase.h"
#include "A_EnemyAttacker.generated.h"

class UBoxComponent;

UCLASS()
class ASTERISK_API AA_EnemyAttacker : public AA_EnemyBase
{
	GENERATED_BODY()
public:
	AA_EnemyAttacker();

private:
	UBoxComponent* AttackBoxComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		UBoxComponent* GetBoxComponent() { return AttackBoxComponent; }

	// ISF_DamageableInterface ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void GetDamage(int32 damage) override;
};
