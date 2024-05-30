#include "A_EnemyAttacker.h"
#include "A_EnemyAttackerController.h"
#include "A_GameMode.h"
#include "A_Player.h"
#include "Components/BoxComponent.h"
#include "../DebugHelpers.h"

AA_EnemyAttacker::AA_EnemyAttacker()
{
	PrimaryActorTick.bCanEverTick = true;

	// ボックスコリジョンを作成し、設定
	AttackBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackBoxComponent = AttackBoxComponent;
	AttackBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AA_EnemyAttacker::BeginPlay()
{
	Super::BeginPlay();
}

void AA_EnemyAttacker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA_EnemyAttacker::GetDamage(int32 damage)
{
	SetCurretnHP(GetCurrentHP() - damage);

	Debug::Print("AttackerEnemy GetDamage : " + FString::FromInt(GetCurrentHP()));

	if (GetCurrentHP() < 1) this->Destroy();
}
