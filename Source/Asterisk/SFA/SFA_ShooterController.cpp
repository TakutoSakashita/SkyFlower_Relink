#include "SFA_ShooterController.h"
#include "SFA_Shooter.h"
#include "SFA_Player.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASFA_ShooterController::ASFA_ShooterController()
	: OwnerShooter(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASFA_ShooterController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASFA_ShooterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(!IsValid(InPawn)) return;
	OwnerShooter = Cast<ASFA_Shooter>(InPawn);
}

void ASFA_ShooterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(OwnerShooter)) return;
	
	switch (OwnerShooter->GetEnemyState())
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

void ASFA_ShooterController::UpdateOnNormal(const float InDeltaTime)
{
	Super::UpdateOnNormal(InDeltaTime);

	if(!IsValid(OwnerShooter)) return;
	
	if(const ASFA_Player* const Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 1)))
	{
		const FVector PlayerPos = Player->GetActorLocation();
		const FVector EnemyPos = OwnerShooter->GetActorLocation();
		const FVector CurrentVector = PlayerPos - EnemyPos;
		
		// 敵キャラクターの回転を更新
		const FRotator NewRotation = CurrentVector.Rotation();
		OwnerShooter->SetActorRotation(NewRotation);

		// 現在のプレイヤーとの距離によってステートを更新
		const float Distance = CurrentVector.Size();
		if (Distance < OwnerShooter->GetAttackableDistance_ShortRange())
		{
			OwnerShooter->SetEnemyState(EASF_EnemyState::ShortRangeAttack);
		}
		else if (Distance < OwnerShooter->GetAttackableDistance_LongRange())
		{
			OwnerShooter->SetEnemyState(EASF_EnemyState::LongRangeAttack);
		}
		else
		{
			// 攻撃可能距離に到達していなければプレイヤーに向かって移動
			const FVector MoveDirection = CurrentVector.GetSafeNormal();
			const FVector MoveVector = MoveDirection * OwnerShooter->GetMoveSpeed();
			OwnerShooter->GetMovementComponent()->Velocity = MoveVector;
		}
	}
}

void ASFA_ShooterController::OnBeginAttack()
{
	Super::OnBeginAttack();
}

void ASFA_ShooterController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
	Super::UpdateOnShortRangeAttack(InDeltaTime);
}

void ASFA_ShooterController::UpdateOnLongRangeAttack(const float InDeltaTime)
{
	Super::UpdateOnLongRangeAttack(InDeltaTime);
}

void ASFA_ShooterController::OnEndAttack()
{
	Super::OnEndAttack();
}

void ASFA_ShooterController::OnBeginDead()
{
	Super::OnBeginDead();
}

void ASFA_ShooterController::UpdateOnDead(const float InDeltaTime)
{
	Super::UpdateOnDead(InDeltaTime);
}

void ASFA_ShooterController::OnEndDead()
{
	Super::OnEndDead();
}

