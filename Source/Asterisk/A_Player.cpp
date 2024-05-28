#include "A_Player.h"
//#include "A_EnemyBase.h"
#include "A_MainCamera.h"
#include "A_GameMode.h"
#include "A_PlayerController.h"
#include "A_MovementInput.h"
#include "A_AttackInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelpers.h"


AA_Player::AA_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	// コンポーネント生成
	MovementInputComponent = CreateDefaultSubobject<UA_MovementInput>(TEXT("MovementInputComponent"));
	AttackInputComponent = CreateDefaultSubobject<UA_AttackInput>(TEXT("AttackInputComponent"));
}

void AA_Player::BeginPlay()
{
	Super::BeginPlay();

	if (AA_GameMode* A_GameMode =
		Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		UE_LOG(LogTemp, Warning, TEXT("SetPlayerCharacter"));

		A_GameMode->SetPlayerCharacter(this);
		m_pCamera = A_GameMode->GetMainCamera();
	}

	if (AA_PlayerController* CustomController =
		Cast<AA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
		CustomController->SetPlayerCharacter(this);
	}

	//test
	Init();
}

void AA_Player::GetDamage(int32 damage)
{
	SetCurretnHP(GetCurrentHP() - damage);

	Debug::Print("A_Player,GetDamage(), CurrentHp = " + FString::FromInt(GetCurrentHP()));

	if (GetCurrentHP() < 1)
	{
		SetCharacterState(ESF_CharacterState::Dead);
		//this->Destroy()
	}
}

/// @brief プレイヤーの状態を常に変更
void AA_Player::UpdateSetPlayerState()
{
	AA_GameMode* const A_GameMode = Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(A_GameMode)) return;

	//ASF_EnemyBase* const LockOnEnemy = SF_GameMode->GetLockOnEnemy();
	//// ターゲットが設定されていなければ通常状態
	//if (!IsValid(SF_GameMode->GetLockOnEnemy()))
	//{
	//	Debug::PrintFixedLine("not found LockOnEnemy");
	//	SetCharacterState(ESF_CharacterState::Normal);
	//	return;
	//}

	//// 敵とプレイヤーの距離を取得し、遠距離・近距離かで状態を変化させる
	//float Distance = (LockOnEnemy->GetActorLocation() - GetActorLocation()).Length();
	//if (Distance < GetAttackableDistance_LongRange())
	//{
	//	if (Distance < GetAttackableDistance_ShortRange())
	//	{
	//		Debug::PrintFixedLine("ShortRange");
	//		SetCharacterState(ESF_CharacterState::ShortRangeAttack);
	//	}
	//	else
	//	{
	//		Debug::PrintFixedLine("LongRange");
	//		SetCharacterState(ESF_CharacterState::LongRangeAttack);
	//	}
	//}
	//// 射程外ならロックオンを解除し通常状態にする
	//else
	//{
	//	Debug::PrintFixedLine("out LongRange");
	//	SF_GameMode->SetLockOnEnemy(nullptr);
	//	SetCharacterState(ESF_CharacterState::Normal);
	//}
}

void AA_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSetPlayerState();
}

void AA_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AA_Player::MoveForward(const float InValue)
{
	if (!MovementInputComponent) return;
	MovementInputComponent->MoveForward(InValue);
}

void AA_Player::MoveAcceleration(const float InValue)
{
	if (!MovementInputComponent) return;
	MovementInputComponent->MoveAcceleration(InValue);
}

void AA_Player::MoveRight(const float InValue)
{
	if (!MovementInputComponent) return;
	MovementInputComponent->MoveRight(InValue);
}

void AA_Player::MoveDash()
{
	if (!MovementInputComponent) return;
	MovementInputComponent->MoveDash();
}

void AA_Player::StopMoveDash()
{
	if (!MovementInputComponent) return;
	MovementInputComponent->StopMoveDash();
}

void AA_Player::MoveJump()
{
	if (!MovementInputComponent) return;
	MovementInputComponent->MoveJump();
}

void AA_Player::BeginShortRangeAttack()
{
	if (!AttackInputComponent) return;
	AttackInputComponent->BeginShortRangeAttack();
}

void AA_Player::EndShortRangeAttack()
{
	if (!AttackInputComponent) return;
	AttackInputComponent->EndShortRangeAttack();
}

void AA_Player::HomingAttack()
{

}

void AA_Player::LaserAttack()
{
	
}

void AA_Player::HomingShoot()
{
	
}

void AA_Player::LockOn()
{

}

void AA_Player::BeginLongRangeAttack()
{
	if (!AttackInputComponent) return;
	AttackInputComponent->BeginLongRangeAttack();
}

void AA_Player::EndLongRangeAttack()
{
	if (!AttackInputComponent) return;
	AttackInputComponent->EndLongRangeAttack();
}

//ASF_EnemyBase* ASF_Player::GetLockOnTarget()
//{
//	if (!IsValid(AttackInputComponent)) return nullptr;
//	return AttackInputComponent->GetLockOnTarget();
//}

//bool AA_Player::GetLockOnStatus()
//{
//	if (!IsValid(AttackInputComponent)) return false;
//	return AttackInputComponent->GetLockOnStatus();
//}
