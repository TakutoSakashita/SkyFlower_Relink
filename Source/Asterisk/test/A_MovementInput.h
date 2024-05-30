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

	// @brief 移動速度倍率
	UPROPERTY(BlueprintReadOnly)
		float moveSpeedBias = 1.f;
	// @brief グライド移動速度倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidSpeedBias = 1.7f;
	// @brief 急降下移動速度倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float diveSpeedBias = 3.5f;
	
	/// @brief 制動倍率
	UPROPERTY(BlueprintReadOnly)
		float airControllBias = 1.f;
	/// @brief グライド制動倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidAirControllBias = 1.5f;

	/// @brief 停止力倍率
	UPROPERTY(BlueprintReadOnly)
		float stopPowerBias = 1.f;
	/// @brief グライド停止力倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidStopPowerBias = 1.5f;

	// @brief 落下速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float gravity = 5.f;
	// @brief 落下速度倍率
	UPROPERTY(BlueprintReadOnly)
		float gravityBias = 1.f;
	// @brief グライド落下速度倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float graidGravityBias = 0.2f;

	// @brief 急降下移行時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float diveThreshold = 3.f;
	// @brief 急降下落下速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float diveGravity = 20.f;

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


protected:
	// 振り向き速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotationSpeed = 8.0f;
	// ダッシュ速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dashSpeed = 1500.0f;

private:
	void CharacterRotate() const;
	void AddForce(const FVector InDirection);

	//////////////////////////////////////// Get関数
	FORCEINLINE AA_GameMode* GetGameMode() const;
	FORCEINLINE AA_MainCamera* GetMainCamera() const;
	FORCEINLINE AA_Player* GetPlayerCharacter() const;
};
