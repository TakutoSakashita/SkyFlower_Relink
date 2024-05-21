// ==================================================
// Filename	:	SF_MoveInput.cpp
// Author	:	22cu0115 �≺��l
// Description: �ړ��̊֐���`
// Notes:		��
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#include "SF_MovementInput.h"
#include "SF_Player.h"
#include "SF_MainCamera.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

using namespace Debug;

USF_MovementInput::USF_MovementInput()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USF_MovementInput::BeginPlay()
{
	Super::BeginPlay();

	m_pCharacter = Cast<ASF_Player>(GetOwner());
	ensure(m_pCharacter != nullptr);
}

void USF_MovementInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USF_MovementInput::MoveForward(const float InValue)
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	//const FRotator Rotation = {
	//	0.f,
	//	UKismetMathLibrary::FindLookAtRotation(SF_Player->GetActorLocation(),FVector(0.f, InValue * 100.f, 0.f)).Yaw,
	//	0.f };
	//UE_LOG(LogTemp, Warning, TEXT("Forward: %f"), SF_Player->GetActorUpVector());

	// ���͕����Ɉړ�
	m_pCharacter->AddMovementInput(GetMainCamera()->GetActorForwardVector(), InValue);

	// ��]
	CharacterRotate();
}

void USF_MovementInput::MoveRight(const float InValue)
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	// ���͕����Ɉړ�
	m_pCharacter->AddMovementInput(GetMainCamera()->GetActorRightVector(), InValue);

	// ��]
	CharacterRotate();
}

void USF_MovementInput::MoveDash()
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	//UE_LOG(LogTemp, Warning, TEXT(": %s"), *m_pCharacter->GetCharacterMovement()->Velocity.ToString());
	//Debug::Print(GetPlayerCharacter()->GetCharacterMovement()->Velocity.ToString());

	// ���̂������ƃL�����N�^�[�̕ێ����Ă���x���V�e�B�̌����ɂ����_�b�V������̂�
	// �v���C���[�̌�����ς��Ă��_�b�V���������Ă���Ƃ��̕����ɂ��������Ȃ�
	//// �L�����N�^�[�̑��x�x�N�g�����擾
	//FVector CharacterVelocity = GetPlayerCharacter()->GetCharacterMovement()->Velocity;
	//
	//// ���x�x�N�g�����[���łȂ����Ƃ��m�F���Ă��琳�K��
	//if (!CharacterVelocity.IsNearlyZero())
	//{
	//	CharacterVelocity.Normalize();
	//	AddForce(CharacterVelocity);
	//}

	// �L�����N�^�[�ƃJ�����̐��ʕ����𑫂��Ă��̌����Ƀ_�b�V������悤��
	AddForce(m_pCharacter->GetActorForwardVector());
}

void USF_MovementInput::MoveJump()
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	// ���͕����Ɉړ�
	//m_pCharacter->AddMovementInput(m_pCharacter->GetActorUpVector(), InValue);
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	m_pCharacter->GetCharacterMovement()->AddImpulse(m_pCharacter->GetActorUpVector() * dashSpeed, true);
}

void USF_MovementInput::AddForce(const FVector InDirection)
{
	// �v���C���[�̑��x���O�ɂ���
	m_pCharacter->GetCharacterMovement()->Velocity = FVector::Zero();
	// �_�b�V��
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	m_pCharacter->GetCharacterMovement()->AddImpulse(InDirection * dashSpeed, true);
}

void USF_MovementInput::CharacterRotate() const
{
	if (!m_pCharacter) return;

	const FVector movement = m_pCharacter->GetLastMovementInputVector();

	// ���͂����鎞������]
	if (movement.X != 0 || movement.Y != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" : %s"), "rotation");
		const FRotator currentRot = { 0.f, m_pCharacter->GetActorRotation().Yaw, 0.f };
		const FRotator targetRot = { 0.f, movement.Rotation().Yaw, 0.f };
		m_pCharacter->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, GetWorld()->GetDeltaSeconds(), rotationSpeed));
	}
}

///////////////////////////FORCEINLINE
ASF_GameMode* USF_MovementInput::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_MainCamera* USF_MovementInput::GetMainCamera() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetMainCamera();
}

ASF_Player* USF_MovementInput::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}