#include "SF_MainCamera.h"
#include "SF_Player.h"
//#include "SF_EnemyBase.h"
#include "SF_GameMode.h"
#include "DebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SF_PlayerController.h"
//#include "SF_FunctionLibrary.h"

ASF_MainCamera::ASF_MainCamera()
//: CameraState(ESF_CameraState::None)
	: ViewPoint(FVector(0.f))
	, MaxPitch(60.f)
	, LockOnRotateSpeed(1.f)
	, CurrentCameraEventType(ESF_CameraEventType::None)
	, FOVInfoMap()
{
	PrimaryActorTick.bCanEverTick = true;

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

void ASF_MainCamera::BeginPlay()
{
	Super::BeginPlay();

	// èâä˙âª
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		SF_GameMode->SetMainCamera(this);

		if (ASF_Player* const SF_Player = SF_GameMode->GetPlayerCharacter())
			ViewPoint = SF_Player->GetActorLocation();
	}


	APlayerController* const PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
		PlayerController->SetViewTargetWithBlend(this);

	ASF_PlayerController* CustomController = Cast<ASF_PlayerController>(PlayerController);
	if (CustomController)
		CustomController->SetMainCamera(this);

	//CameraState = ESF_CameraState::Normal;

}

void ASF_MainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// null check
	ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(SF_GameMode)) return;

	ASF_Player* const SF_Player = SF_GameMode->GetPlayerCharacter();
	if (!IsValid(SF_Player)) return;

	// íçéãì_
	switch (SF_Player->GetCharacterState())
	{
	case ESF_CharacterState::Normal:
		UpdateOnNormal(DeltaTime);
		break;
	case ESF_CharacterState::ShortRangeAttack:
		//UpdateOnShortRangeAttack(DeltaTime);
		UpdateOnNormal(DeltaTime);
		break;
	case ESF_CharacterState::LongRangeAttack:
		//UpdateOnLongRangeAttack(DeltaTime);
		UpdateOnNormal(DeltaTime);
		break;
	default:
		break;
	}

	// ToDo
	switch (CurrentCameraEventType)
	{
	case ESF_CameraEventType::Dash:
		// FOV
		if (FSF_CameraInfo* const CurrentFOVInfo = FOVInfoMap.Find(CurrentCameraEventType))
		{
			// Add/Reduce
			switch (CurrentFOVInfo->CurrentMode)
			{
			case ESF_AddValueMode::Add:
				AddChangeValue(*CurrentFOVInfo);
				break;
			case ESF_AddValueMode::Reduce:
				ReduceChangeValue(*CurrentFOVInfo);
				break;
			}
		}
		//Debug::PrintFixedLine("CurrentCameraEventType : Dash", 120);
		break;
	default:
		//Debug::PrintFixedLine("CurrentCameraEventType : Default", 121);
		break;
	}

	//lock on
	ProcessLockOn(DeltaTime);
}

/// @brief PitchÇÃâÒì]èàóù
/// @param InValue âÒì]ó 
void ASF_MainCamera::AddPitchRotation(float InValue)
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
void ASF_MainCamera::AddYawRotation(float InValue)
{
	if (InValue == 0.f) return;

	//if (IsPlayerLockOn())return;

	// åªç›ÇÃÉJÉÅÉâÇÃâÒì]ó Ç…â¡éZ
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += InValue;

	// ìKóp
	SetActorRotation(NewRotation);
}

void ASF_MainCamera::StartCameraEvent(const ESF_CameraEventType InEventType)
{
	CurrentCameraEventType = InEventType;
	if (FSF_CameraInfo* const CurrentFOVInfo = FOVInfoMap.Find(CurrentCameraEventType))
	{
		CurrentFOVInfo->CurrentMode = ESF_AddValueMode::Add;
		if (FSF_ChangeValueInfo* CurrentChangeValueInfo = CurrentFOVInfo->InfoMap.Find(ESF_AddValueMode::Reduce))
			CurrentChangeValueInfo->CurrentValue = CurrentChangeValueInfo->BeginValue;
	}
}

void ASF_MainCamera::AddChangeValue(FSF_CameraInfo& OutCameraInfo)
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

void ASF_MainCamera::ReduceChangeValue(FSF_CameraInfo& OutCameraInfo)
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

void ASF_MainCamera::CalculateViewPoint(float height)
{
	if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		ViewPoint = Player->GetActorLocation() + FVector(0, 0, height);
	}
}

void ASF_MainCamera::ProcessLockOn(const float InDeltaTime)
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

void ASF_MainCamera::UpdateOnNormal(const float InDeltaTime)
{
	if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		CalculateViewPoint();
		ViewPoint = Player->GetActorLocation();
		SetActorLocation(ViewPoint);
	}
}

void ASF_MainCamera::UpdateOnShortRangeAttack(const float InDeltaTime)
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

void ASF_MainCamera::UpdateOnLongRangeAttack(const float InDeltaTime)
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

bool ASF_MainCamera::IsPlayerLockOn()
{
	//ASF_Player* const Player = USF_FunctionLibrary::GetPlayer(GetWorld());
	//if (!IsValid(Player)) return false;
	//if (!Player->GetLockOnStatus()) return false;

	return true;
}
