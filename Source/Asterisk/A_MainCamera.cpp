#include "A_MainCamera.h"
#include "A_Player.h"
//#include "A_EnemyBase.h"
#include "A_GameMode.h"
#include "DebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "A_PlayerController.h"
//#include "A_FunctionLibrary.h"

AA_MainCamera::AA_MainCamera()
//: CameraState(ESF_CameraState::None)
	: ViewPoint(FVector(0.f))
	, MaxPitch(60.f)
	, LockOnRotateSpeed(1.f)
	, CurrentCameraEventType(ESF_CameraEventType::None)
	, FOVInfoMap()
{
	PrimaryActorTick.bCanEverTick = true;

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (arrow)
		RootComponent = arrow;

	if (IsValid(SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"))))
	{
		SpringArmComponent->SetupAttachment(RootComponent);
		SpringArmComponent->TargetArmLength = 500.f;
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bEnableCameraLag = true;
	}

	if (IsValid(CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"))))
	{
		CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
		CameraComponent->AspectRatio = 1.95f;
	}

}

void AA_MainCamera::BeginPlay()
{
	Super::BeginPlay();

	// èâä˙âª
	if (AA_GameMode* const A_GameMode = Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		A_GameMode->SetMainCamera(this);

		if (AA_Player* const A_Player = A_GameMode->GetPlayerCharacter())
			ViewPoint = A_Player->GetActorLocation();
	}


	APlayerController* const PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
		PlayerController->SetViewTargetWithBlend(this);

	AA_PlayerController* CustomController = Cast<AA_PlayerController>(PlayerController);
	if (CustomController)
		CustomController->SetMainCamera(this);

	//CameraState = ESF_CameraState::Normal;

}

void AA_MainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// null check
	AA_GameMode* const A_GameMode = Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(A_GameMode)) return;
	
	AA_Player* const A_Player = A_GameMode->GetPlayerCharacter();
	if (!IsValid(A_Player)) return;
	
	UpdateOnNormal(DeltaTime);

	//// íçéãì_
	//switch (A_Player->GetCharacterState())
	//{
	//case ESF_CharacterState::Normal:
	//	UpdateOnNormal(DeltaTime);
	//	break;
	//case ESF_CharacterState::ShortRangeAttack:
	//	//UpdateOnShortRangeAttack(DeltaTime);
	//	UpdateOnNormal(DeltaTime);
	//	break;
	//case ESF_CharacterState::LongRangeAttack:
	//	//UpdateOnLongRangeAttack(DeltaTime);
	//	UpdateOnNormal(DeltaTime);
	//	break;
	//default:
	//	break;
	//}
	//
	//// ToDo
	//switch (CurrentCameraEventType)
	//{
	//case ESF_CameraEventType::Dash:
	//	// FOV
	//	if (FSF_CameraInfo* const CurrentFOVInfo = FOVInfoMap.Find(CurrentCameraEventType))
	//	{
	//		// Add/Reduce
	//		switch (CurrentFOVInfo->CurrentMode)
	//		{
	//		case ESF_AddValueMode::Add:
	//			AddChangeValue(*CurrentFOVInfo);
	//			break;
	//		case ESF_AddValueMode::Reduce:
	//			ReduceChangeValue(*CurrentFOVInfo);
	//			break;
	//		}
	//	}
	//	//Debug::PrintFixedLine("CurrentCameraEventType : Dash", 120);
	//	break;
	//default:
	//	//Debug::PrintFixedLine("CurrentCameraEventType : Default", 121);
	//	break;
	//}
	//
	////lock on
	//ProcessLockOn(DeltaTime);
	UpdateRotation(DeltaTime);
}

void AA_MainCamera::UpdateRotation(const float DeltaTime)
{
	// èàóùóéÇøëŒçÙ
	float rotateCorrection = 60.f / (1.0f / DeltaTime);

	// äpìxåvéZ
	FRotator rotation = arrow->GetRelativeRotation();
	// pitchêßå¿
	rotation.Pitch = FMath::Clamp(rotation.Pitch + (inputValue.Y * pitch_sensitivity * rotateCorrection), current_pitch_min, current_pitch_max);
	rotation.Yaw += inputValue.X * yaw_sensitivity * rotateCorrection;
	// ãóó£ï‚ê≥
	float newLength = (-rotation.Pitch - current_pitch_min) / (current_pitch_max - current_pitch_min) * (current_boom_length_max - boom_length_min) + boom_length_min;
	SpringArmComponent->TargetArmLength = newLength;
	// âÒì]
	arrow->SetRelativeRotation(rotation);
}

/// @brief PitchÇÃâÒì]èàóù
/// @param InValue âÒì]ó 
void AA_MainCamera::AddPitchRotation(float InValue)
{
	if (InValue == 0.f) return;

	//if (IsPlayerLockOn())return;
	// åªç›ÇÃÉJÉÅÉâÇÃâÒì]ó Ç…â¡éZ
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += InValue;

	// ï‚ê≥
	if (NewRotation.Pitch >= MaxPitch)
		NewRotation.Pitch = MaxPitch;
	else if (NewRotation.Pitch <= -MaxPitch)
		NewRotation.Pitch = -MaxPitch;

	// ìKóp
	SetActorRotation(NewRotation);
}

/// @brief YawÇÃâÒì]èàóù
/// @param InValue âÒì]ó 
void AA_MainCamera::AddYawRotation(float InValue)
{
	if (InValue == 0.f) return;

	//if (IsPlayerLockOn())return;

	// åªç›ÇÃÉJÉÅÉâÇÃâÒì]ó Ç…â¡éZ
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += InValue;

	// ìKóp
	SetActorRotation(NewRotation);
}

void AA_MainCamera::StartCameraEvent(const ESF_CameraEventType InEventType)
{
	CurrentCameraEventType = InEventType;
	if (FSF_CameraInfo* const CurrentFOVInfo = FOVInfoMap.Find(CurrentCameraEventType))
	{
		CurrentFOVInfo->CurrentMode = ESF_AddValueMode::Add;
		if (FSF_ChangeValueInfo* CurrentChangeValueInfo = CurrentFOVInfo->InfoMap.Find(ESF_AddValueMode::Reduce))
			CurrentChangeValueInfo->CurrentValue = CurrentChangeValueInfo->BeginValue;
	}
}

void AA_MainCamera::AddChangeValue(FSF_CameraInfo& OutCameraInfo)
{
	if (FSF_ChangeValueInfo* const CurrentChangeValueInfo = OutCameraInfo.InfoMap.Find(ESF_AddValueMode::Add))
	{
		CurrentChangeValueInfo->CurrentValue += CurrentChangeValueInfo->AddValue;
		CameraComponent->SetFieldOfView(CurrentChangeValueInfo->CurrentValue);

		if (CurrentChangeValueInfo->CurrentValue > CurrentChangeValueInfo->EndValue)
		{
			OutCameraInfo.CurrentMode = ESF_AddValueMode::Reduce;
			CurrentChangeValueInfo->CurrentValue = CurrentChangeValueInfo->BeginValue;
		}
	}
}

void AA_MainCamera::ReduceChangeValue(FSF_CameraInfo& OutCameraInfo)
{
	if (FSF_ChangeValueInfo* const CurrentChangeValueInfo = OutCameraInfo.InfoMap.Find(ESF_AddValueMode::Reduce))
	{
		CurrentChangeValueInfo->CurrentValue -= CurrentChangeValueInfo->AddValue;
		CameraComponent->SetFieldOfView(CurrentChangeValueInfo->CurrentValue);

		if (CurrentChangeValueInfo->CurrentValue < CurrentChangeValueInfo->EndValue)
		{
			OutCameraInfo.CurrentMode = ESF_AddValueMode::None;
			CurrentChangeValueInfo->CurrentValue = CurrentChangeValueInfo->BeginValue;

			CurrentCameraEventType = ESF_CameraEventType::None;
		}
	}
}

void AA_MainCamera::CalculateViewPoint(float height)
{
	if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		//ViewPoint = Player->GetActorLocation() + FVector(0, 0, height);
	}
}

void AA_MainCamera::ProcessLockOn(const float InDeltaTime)
{
	////null check
	//ASF_Player* const Player = USF_FunctionLibrary::GetPlayer(GetWorld());
	//if (!IsValid(Player)) return;
	//if (!Player->GetLockOnStatus()) return;
	//ASF_EnemyBase* const LockOnEnemy = Player->GetLockOnTarget();
	//if (!IsValid(LockOnEnemy)) return;
	//
	////CalculateViewPoint();
	////SetActorLocation(ViewPoint);
	//
	//const FVector LockOnEnemyPos = LockOnEnemy->GetActorLocation();
	//const FRotator CameraDirection = (LockOnEnemyPos - GetActorLocation()).Rotation();
	//const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), CameraDirection, InDeltaTime, LockOnRotateSpeed);
	//SetActorRotation(NewRotation);

}

void AA_MainCamera::UpdateOnNormal(const float InDeltaTime)
{
	if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		CalculateViewPoint();
		//ViewPoint = Player->GetActorLocation();
		SetActorLocation(ViewPoint);
	}
}

void AA_MainCamera::UpdateOnShortRangeAttack(const float InDeltaTime)
{
	/*

	if (const ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_Player* const Player = SF_GameMode->GetPlayerCharacter();
		ASF_EnemyBase* const LockOnEnemy = SF_GameMode->GetLockOnEnemy();

		if (!IsValid(Player)) return;
		if (!IsValid(LockOnEnemy)) return;

		const FVector LockOnEnemyPos = LockOnEnemy->GetActorLocation();
		const FVector PlayerPos = Player->GetActorLocation();

		ViewPoint = ((LockOnEnemyPos - PlayerPos) / 2.f) + PlayerPos;
		SetActorLocation(ViewPoint);
	}

	*/

}

void AA_MainCamera::UpdateOnLongRangeAttack(const float InDeltaTime)
{
	/*

	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_Player* const Player = SF_GameMode->GetPlayerCharacter();
		ASF_EnemyBase* const LockOnEnemy = SF_GameMode->GetLockOnEnemy();

		if (!IsValid(Player)) return;
		if (!IsValid(LockOnEnemy)) return;

		ViewPoint = Player->GetActorLocation();
		SetActorLocation(ViewPoint);

		const FVector LockOnEnemyPos = LockOnEnemy->GetActorLocation();
		const FRotator CameraDirection = (LockOnEnemyPos - GetActorLocation()).Rotation();
		const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), CameraDirection, InDeltaTime, LockOnRotateSpeed);
		SetActorRotation(NewRotation);
	}

	*/
}

bool AA_MainCamera::IsPlayerLockOn()
{
	//ASF_Player* const Player = USF_FunctionLibrary::GetPlayer(GetWorld());
	//if (!IsValid(Player)) return false;
	//if (!Player->GetLockOnStatus()) return false;
	//
	return true;
}
