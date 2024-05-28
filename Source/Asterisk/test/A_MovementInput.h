#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "A_MovementInput.generated.h"

#define TIME UGameplayStatics::GetGlobalTimeDilation(GetWorld())

class AA_GameMode;
class AA_MainCamera;
class AA_Player;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTERISK_API UA_MovementInput : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UA_MovementInput();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void MoveForward(const float InValue);
	void MoveAcceleration(const float InValue);
	void MoveRight(const float InValue);
	void MoveJump();
	void MoveDash();
	void StopMoveDash();

	void SetGraidSpeedBias() { moveSpeedBias = graidSpeedBias; }
	void SetDiveSpeedBias() { moveSpeedBias = diveSpeedBias; }
	void ResetSpeedBias() { moveSpeedBias = 1.f; }
	void SetGraidGravityBias() { gravityBias = graidGravityBias; }
	void ResetGravityBias() { gravityBias = 1.f; }
	void SetGraidStopPowerBias() { stopPowerBias = graidStopPowerBias; }
	void ResetStopPowerBias() { stopPowerBias = 1.f; }
	void SetGraidAirControlledBias() { airControllBias = graidAirControllBias; }
	void ResetAirControlledBias() { airControllBias = 1.f; }

public:
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ComboMontage;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UAnimInstance* AnimInstance;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief ���͒l
	UPROPERTY(BlueprintReadOnly)
	FVector2D inputValue;
	/// @brief ���͒l�̕␳�l
	FVector2D inputBias;
	/// @brief ����
	bool bInputFwd;
	/// @brief ����
	bool bInputRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitAcceleration = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAcceleration = 2000.f;
	// @brief �ړ����x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed = 100.f;
	// @brief �ړ����x�{��
	UPROPERTY(BlueprintReadOnly)
	float moveSpeedBias = 1.f;
	// @brief �O���C�h�ړ����x�{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidSpeedBias = 1.7f;
	// @brief �}�~���ړ����x�{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float diveSpeedBias = 3.5f;
	// @brief �󒆃_�b�V���X�s�[�h
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airDashSpeed = 20.f;
	// @brief �󒆃_�b�V������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airDashDeceleration = 14.f;
	// @brief �󒆃W�����v�p���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airJumpPower = 20.f;
	// @brief �󒆃W�����v����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airJumpDeceleration = 14.f;
	/// @brief ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airControll = 0.02f;
	/// @brief �����{��
	UPROPERTY(BlueprintReadOnly)
	float airControllBias = 1.f;
	/// @brief �O���C�h�����{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidAirControllBias = 1.5f;
	/// @brief ��~��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float stopPower = 0.01f;
	/// @brief ��~�͔{��
	UPROPERTY(BlueprintReadOnly)
	float stopPowerBias = 1.f;
	/// @brief �O���C�h��~�͔{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidStopPowerBias = 1.5f;
	// @brief ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float friction = 7.f;
	// @brief �������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gravity = 5.f;
	// @brief �������x�{��
	UPROPERTY(BlueprintReadOnly)
	float gravityBias = 1.f;
	// @brief �O���C�h�������x�{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidGravityBias = 0.2f;
	// @brief �}�~���������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float diveGravity = 20.f;
	// @brief �������x����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallingSpeedLimit = 20.f;
	// @brief �}�~���ڍs����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float diveThreshold = 3.f;
	/// @brief ���ĉ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyVelocityValue = 5.f;
	/// @brief ���ĉ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyZVelocity = 10.f;
	/// @brief ���Ď�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyDuration = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ViewVector;

protected:
	/*------------------------------------------------------------------------------------------------------------------------------
	* �e�t���O
	-------------------------------------------------------------------------------------------------------------------------------*/
	/// @brief ���[�g���[�V�����K�p��
	bool bRootMotion = false;
	/// @brief ���V
	UPROPERTY(BlueprintReadOnly)
	bool bFloat;
	/// @brief Wire�ړ���
	UPROPERTY(BlueprintReadOnly)
	bool bWire;
	/// @brief ������ђ�
	UPROPERTY(BlueprintReadOnly)
	bool bForce;
	/// @brief ������
	UPROPERTY(BlueprintReadOnly)
	bool bFly;
	/// @brief �O���C�h��
	UPROPERTY(BlueprintReadOnly)
	bool bGraid;
	/// @brief �}�~����
	UPROPERTY(BlueprintReadOnly)
	bool bDive;

protected:
	/// @brief �d�͍X�V
	/// @param DeltaTime 
	void UpdateGravity(float DeltaTime);

	/// @brief ����
	/// @param DeltaTime
	void UpdateFly(float DeltaTime);
	/// @brief ����
	bool UnderCheck();

	/// @brief �؋󎞊�
	float airborneTime;
	/// @brief �O�t���[���������x
	float beforeGravityAcceleration;

	/// @brief ������ѕ���
	FVector forceVector;
	/// @brief ������ї�
	float forceValue;
	/// @brief ������тɑ΂��錸����
	float forceDecelerationValue;

	/// @brief ���݂̔��ĉ�����
	float currentFlyVelocityValue;
	/// @brief �������ԃ^�C�}�[
	float flyDurationTimer;
	/// @brief ����
	FVector flyVec;

	/// @brief Wire�ړ�����
	FVector wireMoveVector;
	/// @brief Wire�ړ����x
	float wireMoveSpeed;
	/// @brief Wire�ړ�����
	float wireMoveTime;
	/// @brief Wire�ړ�����
	float currentWireMoveTime;

	/// @brief �Ō�̓��̓x�N�g��
	FVector2D beforeMoveVector;
	/// @brief �O�t���[���ʒu
	FVector beforePos;

protected:
	// �U��������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotationSpeed = 8.0f;
	// �_�b�V�����x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float dashSpeed = 1500.0f;

	AA_Player* m_pCharacter;
	AA_MainCamera* m_pMainCamera;

private:
	void CharacterRotate() const;
	void AddForce(const FVector InDirection);

	//////////////////////////////////////// Get�֐�
	FORCEINLINE AA_GameMode* GetGameMode() const;
	FORCEINLINE AA_MainCamera* GetMainCamera() const;
	FORCEINLINE AA_Player* GetPlayerCharacter() const;
};
