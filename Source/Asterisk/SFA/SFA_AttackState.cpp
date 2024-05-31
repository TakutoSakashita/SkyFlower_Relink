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

	// ComboMontage��AnimMontage�ւ̃|�C���^��ێ����Ă���ϐ�
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
	// �R���W�����L��
	Debug::PrintFixedLine("StartCollision");
}

void USFA_AttackState::EndCollision()
{
	// �R���W�����L��
	Debug::PrintFixedLine("StartCollision");
}

void USFA_AttackState::StartCombo()
{
	// �R���{���͎�t�J�n
	ComboAccept = true;
}

void USFA_AttackState::EndCombo()
{
	// �R���{���͎�t�J�n
	ComboAccept = false;
}

void USFA_AttackState::ResetCombo()
{
	// �R���{���Z�b�g
	ComboAccept = true;
	ComboCount = 0;
}
//////////////////////////////////// NotifyEvent
