#pragma once

#include "CoreMinimal.h"
#include "A_CharacterBase.h"
#include "A_Player.generated.h"

class AA_MainCamera;
class UA_MovementInput;
class UA_AttackInput;

UCLASS()
class ASTERISK_API AA_Player : public AA_CharacterBase
{
	GENERATED_BODY()

		////////////////////// override function
public:
	AA_Player();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	////////////////////// custom function
public:
	void MoveForward(const float InValue);
	void MoveAcceleration(const float InValue);
	void MoveRight(const float InValue);
	void MoveJump();
	void MoveDash();
	void StopMoveDash();

	void BeginShortRangeAttack();
	void EndShortRangeAttack();
	void HomingAttack();
	void LaserAttack();

	void HomingShoot();
	void LockOn();
	void BeginLongRangeAttack();
	void EndLongRangeAttack();

	// 振り向き速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rotationSpeed = 8.0f;
	// ダッシュ速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dashSpeed = 1500.0f;

	//ASF_EnemyBase* GetLockOnTarget();
	//bool GetLockOnStatus();
	//


	////////////////////// BlueprintImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
		void Init();

	AA_MainCamera* m_pCamera;

private:
	// ISF_DamageableInterface を介して継承されました
	virtual void GetDamage(int32 damage) override;
	/// @brief プレイヤーの状態を常に変更
	void UpdateSetPlayerState();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UA_MovementInput* MovementInputComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UA_AttackInput* AttackInputComponent;
};