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
	UA_MovementInput();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

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
	UAnimMontage* MoveMontage;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UAnimInstance* AnimInstance;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InitAcceleration = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAcceleration = 2000.f;

	// @brief �ړ����x�{��
	UPROPERTY(BlueprintReadOnly)
		float moveSpeedBias = 1.f;
	// @brief �O���C�h�ړ����x�{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidSpeedBias = 1.7f;
	// @brief �}�~���ړ����x�{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float diveSpeedBias = 3.5f;
	
	/// @brief �����{��
	UPROPERTY(BlueprintReadOnly)
		float airControllBias = 1.f;
	/// @brief �O���C�h�����{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidAirControllBias = 1.5f;

	/// @brief ��~�͔{��
	UPROPERTY(BlueprintReadOnly)
		float stopPowerBias = 1.f;
	/// @brief �O���C�h��~�͔{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidStopPowerBias = 1.5f;

	// @brief �������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float gravity = 5.f;
	// @brief �������x�{��
	UPROPERTY(BlueprintReadOnly)
		float gravityBias = 1.f;
	// @brief �O���C�h�������x�{��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidGravityBias = 0.2f;

	// @brief �}�~���ڍs����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float diveThreshold = 3.f;
	// @brief �}�~���������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float diveGravity = 20.f;

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


protected:
	// �U��������x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotationSpeed = 8.0f;
	// �_�b�V�����x
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dashSpeed = 1500.0f;

private:
	void CharacterRotate() const;
	void AddForce(const FVector InDirection);

	//////////////////////////////////////// Get�֐�
	FORCEINLINE AA_GameMode* GetGameMode() const;
	FORCEINLINE AA_MainCamera* GetMainCamera() const;
	FORCEINLINE AA_Player* GetPlayerCharacter() const;
};
