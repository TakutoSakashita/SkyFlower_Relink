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
	/// @brief 入力値
	UPROPERTY(BlueprintReadOnly)
	FVector2D inputValue;
	/// @brief 入力値の補正値
	FVector2D inputBias;
	/// @brief 入力
	bool bInputFwd;
	/// @brief 入力
	bool bInputRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitAcceleration = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAcceleration = 2000.f;
	// @brief 移動速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed = 100.f;
	// @brief 移動速度倍率
	UPROPERTY(BlueprintReadOnly)
	float moveSpeedBias = 1.f;
	// @brief グライド移動速度倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidSpeedBias = 1.7f;
	// @brief 急降下移動速度倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float diveSpeedBias = 3.5f;
	// @brief 空中ダッシュスピード
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airDashSpeed = 20.f;
	// @brief 空中ダッシュ減衰
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airDashDeceleration = 14.f;
	// @brief 空中ジャンプパワー
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airJumpPower = 20.f;
	// @brief 空中ジャンプ減衰
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airJumpDeceleration = 14.f;
	/// @brief 制動
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float airControll = 0.02f;
	/// @brief 制動倍率
	UPROPERTY(BlueprintReadOnly)
	float airControllBias = 1.f;
	/// @brief グライド制動倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidAirControllBias = 1.5f;
	/// @brief 停止力
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float stopPower = 0.01f;
	/// @brief 停止力倍率
	UPROPERTY(BlueprintReadOnly)
	float stopPowerBias = 1.f;
	/// @brief グライド停止力倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidStopPowerBias = 1.5f;
	// @brief 減速力
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float friction = 7.f;
	// @brief 落下速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gravity = 5.f;
	// @brief 落下速度倍率
	UPROPERTY(BlueprintReadOnly)
	float gravityBias = 1.f;
	// @brief グライド落下速度倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float graidGravityBias = 0.2f;
	// @brief 急降下落下速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float diveGravity = 20.f;
	// @brief 落下速度制限
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallingSpeedLimit = 20.f;
	// @brief 急降下移行時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float diveThreshold = 3.f;
	/// @brief 飛翔加速力
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyVelocityValue = 5.f;
	/// @brief 飛翔加速力
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyZVelocity = 10.f;
	/// @brief 飛翔持続時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyDuration = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ViewVector;

protected:
	/*------------------------------------------------------------------------------------------------------------------------------
	* 各フラグ
	-------------------------------------------------------------------------------------------------------------------------------*/
	/// @brief ルートモーション適用中
	bool bRootMotion = false;
	/// @brief 浮遊
	UPROPERTY(BlueprintReadOnly)
	bool bFloat;
	/// @brief Wire移動中
	UPROPERTY(BlueprintReadOnly)
	bool bWire;
	/// @brief 吹っ飛び中
	UPROPERTY(BlueprintReadOnly)
	bool bForce;
	/// @brief 加速中
	UPROPERTY(BlueprintReadOnly)
	bool bFly;
	/// @brief グライド中
	UPROPERTY(BlueprintReadOnly)
	bool bGraid;
	/// @brief 急降下中
	UPROPERTY(BlueprintReadOnly)
	bool bDive;

protected:
	/// @brief 重力更新
	/// @param DeltaTime 
	void UpdateGravity(float DeltaTime);

	/// @brief 加速
	/// @param DeltaTime
	void UpdateFly(float DeltaTime);
	/// @brief 加速
	bool UnderCheck();

	/// @brief 滞空時間
	float airborneTime;
	/// @brief 前フレーム落下速度
	float beforeGravityAcceleration;

	/// @brief 吹っ飛び方向
	FVector forceVector;
	/// @brief 吹っ飛び力
	float forceValue;
	/// @brief 吹っ飛びに対する減速力
	float forceDecelerationValue;

	/// @brief 現在の飛翔加速力
	float currentFlyVelocityValue;
	/// @brief 持続時間タイマー
	float flyDurationTimer;
	/// @brief 持続
	FVector flyVec;

	/// @brief Wire移動方向
	FVector wireMoveVector;
	/// @brief Wire移動速度
	float wireMoveSpeed;
	/// @brief Wire移動時間
	float wireMoveTime;
	/// @brief Wire移動時間
	float currentWireMoveTime;

	/// @brief 最後の入力ベクトル
	FVector2D beforeMoveVector;
	/// @brief 前フレーム位置
	FVector beforePos;

protected:
	// 振り向き速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotationSpeed = 8.0f;
	// ダッシュ速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float dashSpeed = 1500.0f;

	AA_Player* m_pCharacter;
	AA_MainCamera* m_pMainCamera;

private:
	void CharacterRotate() const;
	void AddForce(const FVector InDirection);

	//////////////////////////////////////// Get関数
	FORCEINLINE AA_GameMode* GetGameMode() const;
	FORCEINLINE AA_MainCamera* GetMainCamera() const;
	FORCEINLINE AA_Player* GetPlayerCharacter() const;
};
