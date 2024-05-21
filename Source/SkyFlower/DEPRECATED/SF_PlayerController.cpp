#include "SF_PlayerController.h"
#include "SF_Player.h"
#include "SF_MainCamera.h"
#include "SF_GameMode.h"
//#include "SF_EnemyBase.h"
//#include "SF_FunctionLibrary.h"
#include "../DebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ASF_PlayerController::ASF_PlayerController()
	:m_pCharacter(nullptr)
	, m_pCamera(nullptr)
{
}

void ASF_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* pPawn = GetPawn();
	ensure(pPawn != nullptr);
	m_pCharacter = Cast<ASF_Player>(pPawn);
	ensure(m_pCharacter != nullptr);

	ASF_GameMode* const GameMode =
		Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ensure(GameMode != nullptr);
	m_pCamera = GameMode->GetMainCamera();
}

void ASF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//movement process
	InputComponent->BindAxis("MoveForward", this, &ASF_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASF_PlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &ASF_PlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ASF_PlayerController::LookUp);
	InputComponent->BindAction("MoveJump", IE_Pressed, this, &ASF_PlayerController::MoveJump);
	InputComponent->BindAction("MoveDash", IE_Pressed, this, &ASF_PlayerController::MoveDash);

	//attack process
	InputComponent->BindAction("BeginNormalAttack", IE_Pressed, this, &ASF_PlayerController::BeginNormalAttack);
	InputComponent->BindAction("EndNormalAttack", IE_Released, this, &ASF_PlayerController::EndNormalAttack);
	InputComponent->BindAction("HomingAttack", IE_Pressed, this, &ASF_PlayerController::HomingAttack);
	InputComponent->BindAction("LaserAttack", IE_Pressed, this, &ASF_PlayerController::LaserAttack);

	InputComponent->BindAction("HomingShoot", IE_Pressed, this, &ASF_PlayerController::HomingShoot);
	InputComponent->BindAction("LockOn", IE_Pressed, this, &ASF_PlayerController::LockOn);
	InputComponent->BindAction("LongRangeAttack", IE_Pressed, this, &ASF_PlayerController::LongRangeAttack);
}

///////////////////////// camera
void ASF_PlayerController::LookUp(const float InValue)
{
	if (!m_pCamera) return;
	m_pCamera->AddPitchRotation(InValue);
}

void ASF_PlayerController::Turn(const float InValue)
{
	if (!m_pCamera) return;
	m_pCamera->AddYawRotation(InValue);

}

///////////////////////// Player movement
void ASF_PlayerController::MoveForward(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveForward(InValue);
}

void ASF_PlayerController::MoveRight(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveRight(InValue);
}

void ASF_PlayerController::MoveJump()
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveJump();
}

void ASF_PlayerController::MoveDash()
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveDash();
}

///////////////////////// Player attack
void ASF_PlayerController::BeginNormalAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->BeginNormalAttack();
}

void ASF_PlayerController::EndNormalAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->EndNormalAttack();

}

void ASF_PlayerController::HomingAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->HomingAttack();
}

void ASF_PlayerController::HomingShoot()
{
	if (!m_pCharacter) return;
	//Debug::Print(" ASF_PlayerController::HomingShoot() ");
	m_pCharacter->HomingShoot();
}

void ASF_PlayerController::LaserAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->LaserAttack();
}

void ASF_PlayerController::LockOn()
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

	//Debug::PrintFixedLine("LOCK ON PRESSED", 190);
	m_pCharacter->LockOn();
}

void ASF_PlayerController::LongRangeAttack()
{
	m_pCharacter->LongRangeAttack();
}
