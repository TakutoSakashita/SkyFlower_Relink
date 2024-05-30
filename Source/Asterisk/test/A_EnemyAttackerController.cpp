#include "A_EnemyAttackerController.h"
#include "A_EnemyAttacker.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AA_EnemyAttackerController::AA_EnemyAttackerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AA_EnemyAttackerController::BeginPlay()
{
	Super::BeginPlay();
}

void AA_EnemyAttackerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	A_EnemyAttacker = Cast<AA_EnemyAttacker>(InPawn);
}

void AA_EnemyAttackerController::Tick(float DeltaTime)
{
	//_EnemyAttacker->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AA_EnemyAttackerController::UpdateState(const float InDeltaTime)
{
}

void AA_EnemyAttackerController::ChooseActionByState(const float InDeltaTime)
{
}

void AA_EnemyAttackerController::UpdateOnNormal(const float InDeltaTime)
{
}

void AA_EnemyAttackerController::OnBeginAttack()
{
}

void AA_EnemyAttackerController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
}

void AA_EnemyAttackerController::UpdateOnLongRangeAttack(const float InDeltaTime)
{
}

void AA_EnemyAttackerController::OnEndAttack()
{
}

void AA_EnemyAttackerController::OnBeginDead()
{
}

void AA_EnemyAttackerController::UpdateOnDead(const float InDeltaTime)
{
}

void AA_EnemyAttackerController::OnEndDead()
{
}

