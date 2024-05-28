#include "A_PlayerController.h"
#include "A_Player.h"
#include "A_MainCamera.h"
#include "A_GameMode.h"
//#include "A_EnemyBase.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AA_PlayerController::AA_PlayerController()
	:m_pCharacter(nullptr)
	, m_pCamera(nullptr)
{
}

void AA_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* pPawn = GetPawn();
	ensure(pPawn != nullptr);
	m_pCharacter = Cast<AA_Player>(pPawn);
	ensure(m_pCharacter != nullptr);

	AA_GameMode* const GameMode =
		Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ensure(GameMode != nullptr);
	m_pCamera = GameMode->GetMainCamera();
}

void AA_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//movement process
	InputComponent->BindAxis("MoveForward", this, &AA_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveAcceleration", this, &AA_PlayerController::MoveAcceleration);
	InputComponent->BindAxis("MoveRight", this, &AA_PlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AA_PlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AA_PlayerController::LookUp);
	InputComponent->BindAction("MoveDash", IE_Pressed, this, &AA_PlayerController::MoveDash);
	InputComponent->BindAction("StopMoveDash", IE_Released, this, &AA_PlayerController::StopMoveDash);
	InputComponent->BindAction("MoveJump", IE_Pressed, this, &AA_PlayerController::MoveJump);

	//attack process
	InputComponent->BindAction("BeginShortRangeAttack", IE_Pressed, this, &AA_PlayerController::BeginShortRangeAttack);
	InputComponent->BindAction("EndShortRangeAttack", IE_Released, this, &AA_PlayerController::EndShortRangeAttack);
	InputComponent->BindAction("HomingAttack", IE_Pressed, this, &AA_PlayerController::HomingAttack);
	InputComponent->BindAction("LaserAttack", IE_Pressed, this, &AA_PlayerController::LaserAttack);

	InputComponent->BindAction("HomingShoot", IE_Pressed, this, &AA_PlayerController::HomingShoot);
	InputComponent->BindAction("LockOn", IE_Pressed, this, &AA_PlayerController::LockOn);
	InputComponent->BindAction("BeginLongRangeAttack", IE_Pressed, this, &AA_PlayerController::BeginLongRangeAttack);
	InputComponent->BindAction("EndLongRangeAttack", IE_Released, this, &AA_PlayerController::EndLongRangeAttack);
}

///////////////////////// camera
void AA_PlayerController::LookUp(const float InValue)
{
	if (!m_pCamera) return;
	m_pCamera->AddPitchRotation(InValue);
}

void AA_PlayerController::Turn(const float InValue)
{
	if (!m_pCamera) return;
	m_pCamera->AddYawRotation(InValue);
}

///////////////////////// Player movement
void AA_PlayerController::MoveForward(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveForward(InValue);
}

void AA_PlayerController::MoveAcceleration(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveAcceleration(InValue);
}

void AA_PlayerController::MoveRight(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveRight(InValue);
}

void AA_PlayerController::MoveJump()
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveJump();
}

void AA_PlayerController::MoveDash()
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveDash();
}

void AA_PlayerController::StopMoveDash()
{
	if (!m_pCharacter) return;
	m_pCharacter->StopMoveDash();
}

///////////////////////// Player attack
void AA_PlayerController::BeginShortRangeAttack()
{
	if (!m_pCharacter) return;
	//UE_LOG(LogTemp, Warning, TEXT("BeginShortRangeAttack"));

	m_pCharacter->BeginShortRangeAttack();
}

void AA_PlayerController::EndShortRangeAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->EndShortRangeAttack();
}

void AA_PlayerController::HomingAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->HomingAttack();
}

void AA_PlayerController::HomingShoot()
{
	Debug::Print(" AA_PlayerController::HomingShoot() ");
	//m_pCharacter->HomingShoot();
}

void AA_PlayerController::LaserAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->LaserAttack();
}

void AA_PlayerController::LockOn()
{
	/*
	ASF_GameMode* const SF_GameMode = USF_FunctionLibrary::GetGameMode(GetWorld());
	if (!IsValid(SF_GameMode)) return;

	// ロックオンされていなければロックオン
	if (!IsValid(SF_GameMode->GetLockOnEnemy()))
	{
		ASF_EnemyBase* const enemy = SF_GameMode->GetNearestEnemy();
		if (!IsValid(enemy)) return;

		SF_GameMode->SetLockOnEnemy(enemy);
	}
	// ロックオンされていれば解除
	else
	{
		SF_GameMode->SetLockOnEnemy(nullptr);
	}
	*/

	Debug::PrintFixedLine("LOCK ON PRESSED", 190);
	//m_pCharacter->LockOn();
}

void AA_PlayerController::BeginLongRangeAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->BeginLongRangeAttack();
}

void AA_PlayerController::EndLongRangeAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->EndLongRangeAttack();
}
