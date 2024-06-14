// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "A_EnemyControllerBase.generated.h"

class AA_GameMode;
class AA_Player;
class UBoxComponent;


UCLASS()
class ASTERISK_API AA_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AA_EnemyControllerBase();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		void SetCanAttack(const bool InCanAttack) { bCanAttack = InCanAttack; }
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		bool GetCanAttack() { return bCanAttack; }

private:
	UPROPERTY(VisibleAnywhere)
		bool bCanAttack = true;
	virtual void UpdateState(const float InDeltaTime) {};
	virtual void ChooseActionByState(const float InDeltaTime) {};

private:
	virtual void UpdateOnNormal(const float InDeltaTime) {};
	virtual void OnBeginAttack() {};
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) {};
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) {};
	virtual void OnEndAttack() {};
	virtual void OnBeginDead() {};
	virtual void UpdateOnDead(const float InDeltaTime) {};
	virtual void OnEndDead() {};

public:
	virtual void Normal(const float InDeltaTime) {};
	virtual void ShortRangeAttack(const float InDeltaTime) {};
	virtual void LongRangeAttack(const float InDeltaTime) {};

public:
	////////////////////////////////////////// Get関数
	FORCEINLINE AA_GameMode* GetGameMode() const;

	FORCEINLINE AA_Player* GetPlayerCharacter() const;
};
