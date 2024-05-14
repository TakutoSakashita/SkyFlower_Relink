// ==================================================
// Filename	:	SF_CharacterBace.h
// Author	:	22cu0105 ���c�� �Ől
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
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Normal				UMETA(DisplayName = "�ʏ펞"),
	BeginAttack			UMETA(DisplayName = "�U���J�n��"),
	ShortRangeAttack	UMETA(DisplayName = "�ߋ����U��"),
	LongRangeAttack		UMETA(DisplayName = "�������U��"),
	EndAttack			UMETA(DisplayName = "�U���I����"),
	BeginDead			UMETA(DisplayName = "���S�J�n��"),
	Dead				UMETA(DisplayName = "���S��"),
	EndDead				UMETA(DisplayName = "���S�I����"),
};

// �L�����N�^�[���ʂ̏����܂Ƃ߂��\����
USTRUCT(BlueprintType)
struct FSF_CharacterInfo
{
	GENERATED_BODY()

public:
	// �ő�HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHP;
	// �ړ����x
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	// �ߐڍU���\����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackableDistance_ShortRange;
	// �������U���\����
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
	//// ����
	//UPROPERTY(VisibleAnywhere, Category = "Visible | Equipment")
	//ASF_WeaponBase* WeaponActor;
	//// ��
	//UPROPERTY(VisibleAnywhere, Category = "Visible | Equipment")
	//ASF_Shield* ShieldActor;

	// �L�����N�^�[�̏��
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
	ESF_CharacterState CharacterState;
	// �L�����N�^�[�̃p�����[�^���
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
	/// @brief ���S���Ă��邩
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	bool IsDead() const {
		return  CharacterState == ESF_CharacterState::BeginDead ||
			CharacterState == ESF_CharacterState::Dead ||
			CharacterState == ESF_CharacterState::EndDead ?
			true : false;
	}
	/// @brief �ߋ����U�������Ă��邩
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	bool IsAttack_ShortRange() const { return CharacterState == ESF_CharacterState::ShortRangeAttack ? true : false; }
	/// @brief �������U�������Ă��邩
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	bool IsAttack_LongRange() const { return CharacterState == ESF_CharacterState::LongRangeAttack ? true : false; }

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void SetAttackableDistance_LongRange(const float InValue) { CharacterParam.AttackableDistance_LongRange = InValue; }

	/// @brief �ߋ����U���\�������擾
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	float GetAttackableDistance_ShortRange() const { return CharacterParam.AttackableDistance_ShortRange; }
	/// @brief �������U���\�������擾
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

	//// ISF_DamageableInterface ����Čp������܂���
	//virtual void GetDamage(int32 damage) override;
};