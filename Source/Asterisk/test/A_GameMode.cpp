#include "A_GameMode.h"
#include "A_Player.h"
#include "A_PlayerController.h"
//#include "A_EnemyManager.h"
#include "../DebugHelpers.h"
#include "Kismet/GameplayStatics.h"
//using namespace Debug;


AA_GameMode::AA_GameMode()
	: PlayerCharacter(nullptr)
	//, EnemyManager(nullptr)
	, MainCamera(nullptr)
	//, LockOnEnemy(nullptr)
	, bIsInHitStop(false)
	, HitStopSpeed(0.5f)
	, HitStopTime(0.f)
	, Timer_HitStop(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = AA_PlayerController::StaticClass();

	// �R���|�[�l���g����
	//EnemyManager = CreateDefaultSubobject<USF_EnemyManager>(TEXT("EnemyManager"));
}

void AA_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AA_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInHitStop)
	{
		// �q�b�g�X�g�b�v���ɂ�����DeltaTime�̒l�ɂ���
		Timer_HitStop += DeltaTime * (1.f / HitStopSpeed);
		if (Timer_HitStop > HitStopTime)
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
			bIsInHitStop = false;
			Timer_HitStop = 0.f;
			HitStopTime = 0.f;
		}
	}
}

// �q�b�g�X�g�b�v�̑��x�A�@�q�b�g�X�g�b�v�����鎞��
void AA_GameMode::StartHitStop(const float InHitStopSpeed, const float InHitStopTime)
{
	HitStopTime = 0.f;

	HitStopSpeed = InHitStopSpeed;
	HitStopTime = InHitStopTime;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), HitStopSpeed);
	bIsInHitStop = true;
}

/// @brief �v���C���[�����ԋ߂��G�̍��W���擾����
/// @return nullptr : �G�����Ȃ�
//ASF_EnemyBase* ASF_GameMode::GetNearestEnemy() const
//{
//	if (!IsValid(EnemyManager))
//	{
//		Debug::Print("not found EnemyManager.");
//		return nullptr;
//	}
//
//	return EnemyManager->GetNearestEnemyPos(PlayerCharacter->GetActorLocation());
//}