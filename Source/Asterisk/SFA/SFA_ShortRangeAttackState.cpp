#include "SFA_ShortRangeAttackState.h"
#include "SFA_Player.h"
// AattackInput
//#include "A_Weapon.h"
#include "Components/BoxComponent.h" 
#include "../DebugHelpers.h"

void USFA_ShortRangeAttackState::OnEnterState()
{
	Super::OnEnterState();

	if (!ComboAccept)return;
	ComboCount++;
	ComboAccept = false;

	// ComboMontageはAnimMontageへのポインタを保持している変数
	if (!IsValid(Player)) {
		Debug::Print("!IsValid(Player)");
		return;
	}

	if (!IsValid(Player->GetMesh())) {
		Debug::Print("!IsValid(Player->GetMesh())");
		return;
	}

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) {
		Debug::Print("!IsValid(AnimInstance)");
		return;
	}


	if (!IsValid(AnimInstance)) return;

	if (AttackMontage && AnimInstance)
	{
		Debug::PrintFixedLine("AttackMontage");

		//UE_LOG(LogTemp, Warning, TEXT("ComboMontage"));

		FString SectionName = FString::Printf(TEXT("Attack0%d"), ComboCount);
		FName SectionFName(*SectionName);

		Player->PlayAnimMontage(AttackMontage, 1.0f, SectionFName);
	}
}

void USFA_ShortRangeAttackState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

}

void USFA_ShortRangeAttackState::OnExitState()
{
	Super::OnExitState();

}

//////////////////////////////////// NotifyEvent
void USFA_ShortRangeAttackState::StartCollision()
{
	// コリジョン有効
	Debug::PrintFixedLine("StartCollision");
}

void USFA_ShortRangeAttackState::EndCollision()
{
	// コリジョン有効
	Debug::PrintFixedLine("StartCollision");
}

void USFA_ShortRangeAttackState::StartCombo()
{
	// コンボ入力受付開始
	ComboAccept = true;
}

void USFA_ShortRangeAttackState::EndCombo()
{
	// コンボ入力受付開始
	ComboAccept = false;
}

void USFA_ShortRangeAttackState::ResetCombo()
{
	// コンボリセット
	ComboAccept = true;
	ComboCount = 0;
}
//////////////////////////////////// NotifyEvent