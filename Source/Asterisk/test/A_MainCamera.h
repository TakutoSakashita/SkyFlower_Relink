#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_MainCamera.generated.h"

class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;

/// @brief �J�����X�e�[�g�̗񋓌^
//UENUM(BlueprintType)
//enum class ESF_CameraState : uint8
//{
//	None = 0			UMETA(DisplayName = "�Ȃ�"),
//	Normal				UMETA(DisplayName = "�ʏ펞"),
//	NormalBattle		UMETA(DisplayName = "�ʏ�o�g����"),
//	CloseBattle			UMETA(DisplayName = "�ߐڃo�g����"),
//};

/// @brief �C�x���g���̏�����Map�ŊǗ����邽�߂̗񋓌^
UENUM(BlueprintType)
enum class ESF_CameraEventType : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Dash				UMETA(DisplayName = "�_�b�V����"),
};

/// @brief �l�̕ω���Ԃ�Map�ŊǗ����邽�߂̗񋓌^
UENUM(BlueprintType)
enum class ESF_AddValueMode : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Add					UMETA(DisplayName = "���@"),
	Reduce				UMETA(DisplayName = "���@"),
};

/// @brief �l�������@�ŕω�������\����
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

/// @brief Map��Map���Ǘ����邽�߂̍\����
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
class ASTERISK_API AA_MainCamera : public AActor
{
	GENERATED_BODY()

		//////////// override function
public:
	AA_MainCamera();
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
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* arrow;
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
	// �f�b�h�]�[��
	bool bDeadZone;
	// �}�j���A���G�C��
	bool bManualAim;
	// ����
	FVector2D inputValue;
	// �f�b�h�]�[��
	UPROPERTY(EditAnywhere)
		float deadZone = 0.05f;
	UPROPERTY(EditAnywhere)
		float pitch_sensitivity = 2.f;
	UPROPERTY(EditAnywhere)
		float yaw_sensitivity = 2.f;

	UPROPERTY(EditAnywhere)
		float pitch_min = -40.f;
	UPROPERTY(EditAnywhere)
		float current_pitch_min = -40.f;
	UPROPERTY(EditAnywhere)
		float dive_pitch_min = -40.f;

	UPROPERTY(EditAnywhere)
		float pitch_max = 65.f;
	UPROPERTY(EditAnywhere)
		float current_pitch_max = 65.f;
	UPROPERTY(EditAnywhere)
		float dive_pitch_max = 30.f;

	UPROPERTY(EditAnywhere)
		float boom_length_min = 180.f;

	UPROPERTY(EditAnywhere)
		float current_boom_length_max = 500.f;
	UPROPERTY(EditAnywhere)
		float boom_length_max = 500.f;
	UPROPERTY(EditAnywhere)
		float dive_boom_length_max = 600.f;
	UPROPERTY(EditAnywhere)
		float graid_boom_length_max = 520.f;
	UPROPERTY(EditAnywhere)
		float fly_boom_length_max = 480.f;

	void SetDiveBoomLength() { current_boom_length_max = dive_boom_length_max; }
	void SetViewPoint(FVector vector) { ViewPoint = vector; }
	void SetGraidBoomLength() { current_boom_length_max = graid_boom_length_max; }
	void SetFlyBoomLength() { current_boom_length_max = fly_boom_length_max; }
	void ResetBoomLength() { current_boom_length_max = boom_length_max; }
	void SetDivePitch() { current_pitch_min = dive_pitch_min; current_pitch_max = dive_pitch_max; }
	void ResetPitch() { current_pitch_min = pitch_min; current_pitch_max = pitch_max; }

	//void SetManualAim(const bool aim) { bManualAim = aim; };
private:
	// �f�b�h�]�[��
//	bool bDeadZone;
	// �}�j���A���G�C��
//	bool bManualAim;
	// ����
//	FVector2D inputValue;
	void UpdateRotation(const float DeltaTime);

public:
	//void SetCameraState(const ESF_CameraState InCameraState) { CameraState = InCameraState; }
	//ESF_CameraState GetCameraState() const { return CameraState; }
	FVector GetViewPoint() const { return ViewPoint; }
	ESF_CameraEventType GetCurrentCameraEventType() const { return CurrentCameraEventType; }
	bool IsPlayerLockOn();
};
