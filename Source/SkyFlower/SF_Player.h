// ==================================================
// Filename	:	SF_Player.h
// Author	:	22cu0115 坂下 拓人
// Description:
// Update	:	2024/04/08
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_CharacterBase.h"
#include "SF_Player.generated.h"

class USF_MovementInput;
//class USF_AttackInput;
//class ASF_EnemyBase;
//class ASF_WeaponBase;

UCLASS()
class SKYFLOWER_API ASF_Player : public ASF_CharacterBase
{
	GENERATED_BODY()

	////////////////////// override function
public:
	ASF_Player();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	////////////////////// custom function
public:
	void MoveForward(const float InValue);
	void MoveRight(const float InValue);
	void MoveJump();
	void MoveDash();

	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

	void HomingShoot();
	void LockOn();
	void LongRangeAttack();

	//ASF_EnemyBase* GetLockOnTarget();
	bool GetLockOnStatus();

	//UFUNCTION(BlueprintCallable)
	//ASF_WeaponBase* GetWeapon() const { return Weapon; };
	//UPROPERTY(BlueprintReadWrite)
	//ASF_WeaponBase* Weapon = nullptr;

	////////////////////// BlueprintImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USF_MovementInput* MovementInputComponent;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	//USF_AttackInput* AttackInputComponent;

private:
	//// ISF_DamageableInterface を介して継承されました
	//virtual void GetDamage(int32 damage) override;
	/// @brief プレイヤーの状態を常に変更
	void UpdateSetPlayerState();
};