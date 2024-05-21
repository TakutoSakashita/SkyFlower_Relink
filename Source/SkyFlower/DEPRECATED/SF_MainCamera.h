// ==================================================
// Filename	:	SF_MainCamera.h
// Author	:	22cu0105 小田島 稜人
// Description:
// Update	:	2024/04/05
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_MainCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

/// @brief カメラステートの列挙型
//UENUM(BlueprintType)
//enum class ESF_CameraState : uint8
//{
//	None = 0			UMETA(DisplayName = "なし"),
//	Normal				UMETA(DisplayName = "通常時"),
//	NormalBattle		UMETA(DisplayName = "通常バトル時"),
//	CloseBattle			UMETA(DisplayName = "近接バトル時"),
//};

/// @brief イベント時の処理をMapで管理するための列挙型
UENUM(BlueprintType)
enum class ESF_CameraEventType : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
	Dash				UMETA(DisplayName = "ダッシュ時"),
};

/// @brief 値の変化状態をMapで管理するための列挙型
UENUM(BlueprintType)
enum class ESF_AddValueMode : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
	Add					UMETA(DisplayName = "加法"),
	Reduce				UMETA(DisplayName = "減法"),
};

/// @brief 値を加減法で変化させる構造体
USTRUCT(BlueprintType)
struct FSF_ChangeValueInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BeginValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EndValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AddValue;

public:
	FSF_ChangeValueInfo()
		: BeginValue(0.f)
		, EndValue(0.f)
		, CurrentValue(0.f)
		, AddValue(0.f)
	{}
};

/// @brief MapでMapを管理するための構造体
USTRUCT(BlueprintType)
struct FSF_CameraInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESF_AddValueMode CurrentMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ESF_AddValueMode, FSF_ChangeValueInfo> InfoMap;

public:
	FSF_CameraInfo()
		: CurrentMode(ESF_AddValueMode::None)
		, InfoMap()
	{}
};

//------------------------------------------------------------------

UCLASS()
class SKYFLOWER_API ASF_MainCamera : public AActor
{
	GENERATED_BODY()

	//////////// override function
public:
	ASF_MainCamera();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	//////////////// custom function
public:
	void AddPitchRotation(float InValue);
	void AddYawRotation(float InValue);

	void StartCameraEvent(const ESF_CameraEventType InEventType);
	void AddChangeValue(FSF_CameraInfo& OutCameraInfo);
	void ReduceChangeValue(FSF_CameraInfo& OutCameraInfo);

private:
	void CalculateViewPoint(float height = 100.f/*, FRotator rotate = FRotator(-45, 0, 0)*/);/* pitch , yaw, roll */
	void ProcessLockOn(const float InDeltaTime);
	void UpdateOnNormal(const float InDeltaTime);
	void UpdateOnShortRangeAttack(const float InDeltaTime);
	void UpdateOnLongRangeAttack(const float InDeltaTime);

	//////////////// custom parameter
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera | Visible", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera | Visible", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	//UPROPERTY(VisibleAnywhere, Category = "Camera | Visible")
	//ESF_CameraState CameraState;

	UPROPERTY(VisibleAnywhere, Category = "Camera | Visible")
	FVector ViewPoint;
	UPROPERTY(EditAnywhere, Category = "Camera | Edit")
	float MaxPitch;
	UPROPERTY(EditAnywhere, Category = "Camera | Edit")
	float LockOnRotateSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Camera | Visible")
	ESF_CameraEventType CurrentCameraEventType;

	UPROPERTY(EditAnywhere, Category = "Camera | Edit")
	TMap<ESF_CameraEventType, FSF_CameraInfo> FOVInfoMap;

public:
	//void SetCameraState(const ESF_CameraState InCameraState) { CameraState = InCameraState; }
	//ESF_CameraState GetCameraState() const { return CameraState; }
	FVector GetViewPoint() const { return ViewPoint; }
	ESF_CameraEventType GetCurrentCameraEventType() const { return CurrentCameraEventType; }
	bool IsPlayerLockOn();
};
