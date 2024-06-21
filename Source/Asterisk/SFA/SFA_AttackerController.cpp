#include "SFA_AttackerController.h"
#include "SFA_Attacker.h"
#include "SFA_Player.h"
#include "../DebugHelpers.h"
#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASFA_AttackerController::ASFA_AttackerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASFA_AttackerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASFA_AttackerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(InPawn)) return;

	OwnerAttacker = Cast<ASFA_Attacker>(InPawn);
}

void ASFA_AttackerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(OwnerAttacker)) return;
	
	switch (OwnerAttacker->GetEnemyState())
	{
	case EASF_EnemyState::Normal:
		UpdateOnNormal(DeltaTime);
		break;
	case EASF_EnemyState::BeginAttack:
		OnBeginAttack();
		break;
	case EASF_EnemyState::ShortRangeAttack:
		UpdateOnShortRangeAttack(DeltaTime);
		break;
	case EASF_EnemyState::LongRangeAttack:
		UpdateOnLongRangeAttack(DeltaTime);
		break;
	case EASF_EnemyState::EndAttack:
		OnEndAttack();
		break;
	case EASF_EnemyState::BeginDead:
		OnBeginDead();
		break;
	case EASF_EnemyState::Dead:
		UpdateOnDead(DeltaTime);
		break;
	case EASF_EnemyState::EndDead:
		OnEndDead();
		break;
	}
}

void ASFA_AttackerController::UpdateOnNormal(const float InDeltaTime)
{
	Super::UpdateOnNormal(InDeltaTime);

	if (!IsValid(OwnerAttacker)) return;
	if (!IsValid(OwnerAttacker->GetMovementComponent()))
	{
		Debug::PrintFixedLine("AttackerController : MovementComponent Is NULL.");
		return;
	}

	if(const ASFA_Player* const Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		const FVector PlayerPos = Player->GetActorLocation();
		const FVector EnemyPos = OwnerAttacker->GetActorLocation();
		const FVector CurrentVector = PlayerPos - EnemyPos;
		
		// 敵キャラクターの回転を更新
		const FRotator NewRotation = CurrentVector.Rotation();
		OwnerAttacker->SetActorRotation(NewRotation);

		// 現在のプレイヤーとの距離によってステートを更新
		//const float Distance = CurrentVector.Size();
		//if (Distance < OwnerAttacker->GetAttackableDistance_ShortRange())
		//{
		//	OwnerAttacker->SetEnemyState(EASF_EnemyState::ShortRangeAttack);
		//}
		//else if (Distance < OwnerAttacker->GetAttackableDistance_LongRange())
		//{
		//	OwnerAttacker->SetEnemyState(EASF_EnemyState::LongRangeAttack);
		//}
		//else
		{
			// 攻撃可能距離に到達していなければプレイヤーに向かって移動
			const FVector MoveDirection = CurrentVector.GetSafeNormal();
			const FVector MoveVector = MoveDirection * OwnerAttacker->GetMoveSpeed();
			OwnerAttacker->GetMovementComponent()->Velocity = MoveVector;
		}
	}
}

void ASFA_AttackerController::OnBeginAttack()
{
	Super::OnBeginAttack();
}

void ASFA_AttackerController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
	Super::UpdateOnShortRangeAttack(InDeltaTime);
}

void ASFA_AttackerController::UpdateOnLongRangeAttack(const float InDeltaTime)
{
	Super::UpdateOnLongRangeAttack(InDeltaTime);
}

void ASFA_AttackerController::OnEndAttack()
{
	Super::OnEndAttack();
}

void ASFA_AttackerController::OnBeginDead()
{
	Super::OnBeginDead();
}

void ASFA_AttackerController::UpdateOnDead(const float InDeltaTime)
{
	Super::UpdateOnDead(InDeltaTime);
}

void ASFA_AttackerController::OnEndDead()
{
	Super::OnEndDead();
}

