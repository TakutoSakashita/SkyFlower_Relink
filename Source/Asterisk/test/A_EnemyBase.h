#pragma once

#include "CoreMinimal.h"
#include "A_CharacterBase.h"
#include "A_EnemyBase.generated.h"

class AA_GameMode;
class AA_Player;

UCLASS()
class ASTERISK_API AA_EnemyBase : public AA_CharacterBase
{
	GENERATED_BODY()

public:
	AA_EnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		float GetAttackCooldown() { return AttackCooldown; }
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		void SetCanAttack(const bool InCanAttack) { bCanAttack = InCanAttack; }
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		bool GetCanAttack() { return bCanAttack; }

private:
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
		float AttackCooldown = 2.0f; // ìÀåÇä‘äu
	UPROPERTY(VisibleAnywhere, Category = "EnemyBase")
		bool bCanAttack = true;
	virtual void UpdateState(const float InDeltaTime) {};
	virtual void ChooseActionByState(const float InDeltaTime) {};

private:
	virtual void OnEndDead() override;

	// ISF_DamageableInterface ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void GetDamage(int32 damage) override;

public:
	////////////////////////////////////////// Getä÷êî
	FORCEINLINE AA_GameMode* GetGameMode() const;

	FORCEINLINE AA_Player* GetPlayerCharacter() const;
};
