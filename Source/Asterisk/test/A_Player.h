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
	/********************MovementInput********************/

	// 前方向移動処理
	void MoveForward(const float InValue);
	// 横方向移動処理
	void MoveRight(const float InValue);
	// 前方向にダッシュする
	void StartMoveDash();
	void EndMoveDash();
	// 上方向移動処理
	void StartMoveJump();
	void EndMoveJump();

	/********************AttackInput********************/

	// 近距離攻撃
	void BeginShortRangeAttack();
	void EndShortRangeAttack();
	// 遠距離攻撃
	void BeginLongRangeAttack();
	void EndLongRangeAttack();
	//
	void HomingAttack();
	void HomingShoot();
	void LaserAttack();
	//
	void LockOn();

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