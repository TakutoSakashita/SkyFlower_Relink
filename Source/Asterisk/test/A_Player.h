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

	// �O�����ړ�����
	void MoveForward(const float InValue);
	// �������ړ�����
	void MoveRight(const float InValue);
	// �O�����Ƀ_�b�V������
	void StartMoveDash();
	void EndMoveDash();
	// ������ړ�����
	void StartMoveJump();
	void EndMoveJump();

	/********************AttackInput********************/

	// �ߋ����U��
	void BeginShortRangeAttack();
	void EndShortRangeAttack();
	// �������U��
	void BeginLongRangeAttack();
	void EndLongRangeAttack();
	//
	void HomingAttack();
	void HomingShoot();
	void LaserAttack();
	//
	void LockOn();

	// �U��������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rotationSpeed = 8.0f;
	// �_�b�V�����x
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
	// ISF_DamageableInterface ����Čp������܂���
	virtual void GetDamage(int32 damage) override;
	/// @brief �v���C���[�̏�Ԃ���ɕύX
	void UpdateSetPlayerState();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UA_MovementInput* MovementInputComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UA_AttackInput* AttackInputComponent;
};