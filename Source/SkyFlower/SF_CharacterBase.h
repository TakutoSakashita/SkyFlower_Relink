// ==================================================
// Filename	:	SF_CharacterBace.h
// Author	:	22cu0105 小田島 稜人
// Description:
// Update	:	2024/04/05 init
//				2024/04/18 CharacterState
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SF_CharacterBase.generated.h"
//#include "SF_DamageableInterface.h"

//class ASF_EquipmentBase;
//class ASF_WeaponBase;
//class ASF_Shield;

UENUM(BlueprintType)
enum class ESF_CharacterState : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
	Normal				UMETA(DisplayName = "通常時"),
	BeginAttack			UMETA(DisplayName = "攻撃開始時"),
	ShortRangeAttack	UMETA(DisplayName = "近距離攻撃"),
	LongRangeAttack		UMETA(DisplayName = "遠距離攻撃"),
	EndAttack			UMETA(DisplayName = "攻撃終了時"),
	BeginDead			UMETA(DisplayName = "死亡開始時"),
	Dead				UMETA(DisplayName = "死亡中"),
	EndDead				UMETA(DisplayName = "死亡終了時"),
};

// キャラクター共通の情報をまとめた構造体
USTRUCT(BlueprintType)
struct FSF_CharacterInfo
{
	GENERATED_BODY()

public:
	// 最大HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHP;
	// 移動速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	// 近接攻撃可能距離
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackableDistance_ShortRange;
	// 遠距離攻撃可能距離
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackableDistance_LongRange;

public:
	FSF_CharacterInfo()
		: MaxHP(100.f)
		, MoveSpeed(600.f)
		, AttackableDistance_ShortRange(500.f)
		, AttackableDistance_LongRange(2000.f)
	{}
};

UCLASS()
class SKYFLOWER_API ASF_CharacterBase : public ACharacter//, public ISF_DamageableInterface
{
	GENERATED_BODY()

public:
	ASF_CharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	//void EquipWeapon(ASF_WeaponBase* const InWeapon, const FName& InSoketName);
	//void EquipShield(ASF_Shield* const InShield, const FName& InSoketName);

private:
	//// 武器
	//UPROPERTY(VisibleAnywhere, Category = "Visible | Equipment")
	//ASF_WeaponBase* WeaponActor;
	//// 盾
	//UPROPERTY(VisibleAnywhere, Category = "Visible | Equipment")
	//ASF_Shield* ShieldActor;

	// キャラクターの状態
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
	ESF_CharacterState CharacterState;
	// キャラクターのパラメータ情報
	UPROPERTY(EditAnywhere, Category = "Edit | Param")
	FSF_CharacterInfo CharacterParam;

	// HP
	UPROPERTY()
	float CurrentHP;

public:
	//ASF_WeaponBase* GetWeaponActor() const { return WeaponActor; }
	//ASF_Shield* GetShieldActor() const { return ShieldActor; }

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void SetCharacterState(const ESF_CharacterState InCharacterState) { CharacterState = InCharacterState; }
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	ESF_CharacterState GetCharacterState() { return CharacterState; }
	/// @brief 死亡しているか
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	bool IsDead() const {
		return  CharacterState == ESF_CharacterState::BeginDead ||
			CharacterState == ESF_CharacterState::Dead ||
			CharacterState == ESF_CharacterState::EndDead ?
			true : false;
	}
	/// @brief 近距離攻撃をしているか
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	bool IsAttack_ShortRange() const { return CharacterState == ESF_CharacterState::ShortRangeAttack ? true : false; }
	/// @brief 遠距離攻撃をしているか
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	bool IsAttack_LongRange() const { return CharacterState == ESF_CharacterState::LongRangeAttack ? true : false; }

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void SetAttackableDistance_LongRange(const float InValue) { CharacterParam.AttackableDistance_LongRange = InValue; }

	/// @brief 近距離攻撃可能距離を取得
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	float GetAttackableDistance_ShortRange() const { return CharacterParam.AttackableDistance_ShortRange; }
	/// @brief 遠距離攻撃可能距離を取得
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	float GetAttackableDistance_LongRange() const { return CharacterParam.AttackableDistance_LongRange; }

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void SetCurretnHP(const float InHP) { CurrentHP = InHP; }
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	float GetCurrentHP() const { return CurrentHP; }

private:
	virtual void UpdateOnNormal(const float InDeltaTime) {}
	virtual void OnBeginAttack() {}
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) {}
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) {}
	virtual void OnEndAttack() {}
	virtual void OnBeginDead() {}
	virtual void UpdateOnDead(const float InDeltaTime) {}
	virtual void OnEndDead() {}

	//// ISF_DamageableInterface を介して継承されました
	//virtual void GetDamage(int32 damage) override;
};