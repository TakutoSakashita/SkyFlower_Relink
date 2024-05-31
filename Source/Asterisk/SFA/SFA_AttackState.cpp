#include "SFA_AttackState.h"
#include "SFA_Player.h"
// AattackInput
//#include "A_Weapon.h"
#include "Components/BoxComponent.h" 
#include "../DebugHelpers.h"


USFA_AttackState::USFA_AttackState()
{
}

void USFA_AttackState::OnEnterState()
{
	Super::OnEnterState();

	if (!ComboAccept)return;
	ComboCount++;
	ComboAccept = false;

	//GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

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

void USFA_AttackState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

}

void USFA_AttackState::OnExitState()
{
	Super::OnExitState();

}

//////////////////////////////////// NotifyEvent
void USFA_AttackState::StartCollision()
{
	// コリジョン有効
	Debug::PrintFixedLine("StartCollision");
}

void USFA_AttackState::EndCollision()
{
	// コリジョン有効
	Debug::PrintFixedLine("StartCollision");
}

void USFA_AttackState::StartCombo()
{
	// コンボ入力受付開始
	ComboAccept = true;
}

void USFA_AttackState::EndCombo()
{
	// コンボ入力受付開始
	ComboAccept = false;
}

void USFA_AttackState::ResetCombo()
{
	// コンボリセット
	ComboAccept = true;
	ComboCount = 0;
}
//////////////////////////////////// NotifyEvent
