// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFA_IDamageable.h"
#include "SFA_EnemyBase.generated.h"

class UNiagaraComponent;
class USphereComponent;
class UArrowComponent;
class UStaticMeshComponent;
class ASFA_Player;
class UParticleSystem;
class USoundBase;

UENUM(BlueprintType)
enum class EASF_EnemyState : uint8
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

USTRUCT(BlueprintType)
struct FASF_EnemyParam
{
	GENERATED_BODY()

public:
	// 最大HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;
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
	FASF_EnemyParam()
		: MaxHealth(100.f)
		, MoveSpeed(600.f)
		, AttackableDistance_ShortRange(500.f)
		, AttackableDistance_LongRange(2000.f)
	{}
};

UCLASS()
class ASTERISK_API ASFA_EnemyBase : public APawn, public ISFA_IDamageable
{
	GENERATED_BODY()

public:
	ASFA_EnemyBase();

	////////////////////////////////////////////////// Override
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	//~BEGIN ISFA_IDamageable
public:
	virtual void TakeDamage(AActor* Aggressor, float Damage) override;
	
private:
	////////////////////////////////////////////////// Custom
	/// @brief エネミーの状態
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EASF_EnemyState EnemyState;
	/// @brief エネミーのパラメータ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FASF_EnemyParam EnemyParam;

public:
	////////////////////////////////////////////////// EnemyState
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
	void SetCharacterState(const EASF_EnemyState InEnemyState) { EnemyState = InEnemyState; }
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	EASF_EnemyState GetCharacterState() { return EnemyState; }
	/// @brief 死亡しているか
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
	bool IsDead() const { 
		return  EnemyState == EASF_EnemyState::BeginDead ||
				EnemyState == EASF_EnemyState::Dead ||
				EnemyState == EASF_EnemyState::EndDead ? 
				true : false;
	}
	/// @brief 近距離攻撃をしているか
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
	bool IsAttack_ShortRange() const { return EnemyState == EASF_EnemyState::ShortRangeAttack ? true : false; }
	/// @brief 遠距離攻撃をしているか
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
	bool IsAttack_LongRange() const { return EnemyState == EASF_EnemyState::LongRangeAttack ? true : false; }

	////////////////////////////////////////////////// EnemyParam
	/// @brief 近距離攻撃可能距離を取得
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	float GetAttackableDistance_ShortRange() const { return EnemyParam.AttackableDistance_ShortRange; }
	/// @brief 遠距離攻撃可能距離を取得
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	float GetAttackableDistance_LongRange() const { return EnemyParam.AttackableDistance_LongRange; }

private:
	UFUNCTION()
	void Die();
	UPROPERTY()
	float Health = 100.f;
	//~END


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ASFA_Player* PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathEffect;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
};
