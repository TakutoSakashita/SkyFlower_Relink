#include "A_MovementInput.h"
#include "A_GameMode.h"
#include "A_Player.h"
#include "A_MainCamera.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../DebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

using namespace Debug;

UA_MovementInput::UA_MovementInput()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UA_MovementInput::BeginPlay()
{
	Super::BeginPlay();
}

void UA_MovementInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ����
	UpdateFly(DeltaTime);
	// �d��
	UpdateGravity(DeltaTime);
}

void UA_MovementInput::MoveForward(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	// ���͂����鎞������]
	const FVector movement = GetPlayerCharacter()->GetLastMovementInputVector();

	if (movement.X != 0 || movement.Y != 0)
	{
		GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::Fly);
	}
	else
	{
		GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::Float);
		GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = InitAcceleration;
		AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Stop(0.2f, MoveMontage);

	}
	// ���͕����Ɉړ�
	GetPlayerCharacter()->AddMovementInput(GetMainCamera()->GetActorForwardVector(), InValue);

	// ��]
	CharacterRotate();
}

void UA_MovementInput::MoveRight(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	// ���͕����Ɉړ�
	GetPlayerCharacter()->AddMovementInput(GetMainCamera()->GetActorRightVector(), InValue);

	// ��]
	CharacterRotate();
}

void UA_MovementInput::StartMoveDash()
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::Fly);

	// �L�����N�^�[�ƃJ�����̐��ʕ����𑫂��Ă��̌����Ƀ_�b�V������悤��
	AddForce(GetPlayerCharacter()->GetActorForwardVector());

	GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = MaxAcceleration;

	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	GetPlayerCharacter()->PlayAnimMontage(MoveMontage, 1.0f, "Avoid");

}

void UA_MovementInput::EndMoveDash()
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::Normal);

	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = InitAcceleration;
	AnimInstance->Montage_Stop(0.2f, MoveMontage);
}

void UA_MovementInput::StartMoveJump()
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	GetPlayerCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();

	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	if (!AnimInstance->Montage_IsPlaying(MoveMontage))
	{
		GetPlayerCharacter()->PlayAnimMontage(MoveMontage, 1.0f, "Avoid");
	}

	// ���͕����Ɉړ�
	//m_pCharacter->AddMovementInput(m_pCharacter->GetActorUpVector(), InValue);
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	GetPlayerCharacter()->GetCharacterMovement()->AddImpulse(GetPlayerCharacter()->GetActorUpVector() * dashSpeed, true);
}

void UA_MovementInput::EndMoveJump()
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;
}

void UA_MovementInput::AddForce(const FVector InDirection)
{
	// �v���C���[�̑��x���O�ɂ���
	GetPlayerCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
	// �_�b�V��
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	GetPlayerCharacter()->GetCharacterMovement()->AddImpulse(InDirection * dashSpeed, true);
}

void UA_MovementInput::CharacterRotate() const
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	const FVector movement = GetPlayerCharacter()->GetLastMovementInputVector();

	// ���͂����鎞������]
	if (movement.X != 0 || movement.Y != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" : %s"), "rotation");
		const FRotator currentRot = { 0.f, GetPlayerCharacter()->GetActorRotation().Yaw, 0.f };
		const FRotator targetRot = { 0.f, movement.Rotation().Yaw, 0.f };
		GetPlayerCharacter()->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, GetWorld()->GetDeltaSeconds(), rotationSpeed));
	}
}

/// @brief �d�͍X�V
/// @param DeltaTime 
void UA_MovementInput::UpdateGravity(float DeltaTime)
{
	GetMainCamera()->SetViewPoint(GetPlayerCharacter()->GetActorLocation());

	// ���V��
	//if (GetPlayerCharacter()->GetCharacterState() == ESF_CharacterState::Float) return;

	float gravityAcceleration = 0;

	// ���Ē�
	if (GetPlayerCharacter()->GetCharacterState() == ESF_CharacterState::Fly)
	{
		airborneTime = 0;
		gravityAcceleration = 0;
		ResetSpeedBias();
		return;
	}

	if (UnderCheck())
	{
		airborneTime = 0;
		gravityAcceleration = 0.f;
		bDive = false;
		//UE_LOG(LogTemp, Log, TEXT("Dive : moveComp : NotUpdateGravity"));
		GetMainCamera()->SetViewPoint(GetPlayerCharacter()->GetActorLocation());
		if (!bGraid)
		{
			ResetSpeedBias();
			if (IsValid(GetMainCamera()))
			{
				GetMainCamera()->ResetBoomLength();
				GetMainCamera()->ResetPitch();
			}
		}
	}
	else
	{
		airborneTime += DeltaTime;
		if (airborneTime >= diveThreshold)
		{
			GetMainCamera()->SetViewPoint(GetPlayerCharacter()->GetActorLocation() - ViewVector);

			bDive = true;
			gravityAcceleration = diveGravity;
			SetDiveSpeedBias();
			//UE_LOG(LogTemp, Log, TEXT("Dive : moveComp : diveThreshold"));

			if (IsValid(GetMainCamera()))
			{
				GetMainCamera()->SetDiveBoomLength();
				GetMainCamera()->SetDivePitch();
			}
		}
		else
		{
			bDive = false;
			//UE_LOG(LogTemp, Log, TEXT("Dive : moveComp : UpdateGravity"));
			GetMainCamera()->SetViewPoint(GetPlayerCharacter()->GetActorLocation());

			gravityAcceleration = 0.5f * gravity * gravityBias * pow(airborneTime, 2) * TIME;


			{
				ResetSpeedBias();
				if (IsValid(GetMainCamera()))
				{
					GetMainCamera()->ResetBoomLength();
					GetMainCamera()->ResetPitch();
				}
			}
		}
	}

	// �������x��ۑ�
	beforeGravityAcceleration = gravityAcceleration;

	////���x����::��X�_�C�r���O���[�h�Ƃ��ɕύX���郈
	//if (beforeGravityAcceleration > FallingSpeedLimit) {
	//	beforeGravityAcceleration = FallingSpeedLimit;
	//}

	// �ړ�
	GetPlayerCharacter()->SetActorLocation(GetPlayerCharacter()->GetActorLocation() +
		FVector(0, 0, -1) * beforeGravityAcceleration);
}

/// @brief ����
/// @param DeltaTime
void UA_MovementInput::UpdateFly(float DeltaTime)
{
	if (GetPlayerCharacter()->GetCharacterState() != ESF_CharacterState::Fly)return;

	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = MaxAcceleration;

	if (AnimInstance && !AnimInstance->Montage_IsPlaying(MoveMontage))
	{
		GetPlayerCharacter()->PlayAnimMontage(MoveMontage, 1.0f, "Fly");
	}
}

bool UA_MovementInput::UnderCheck()
{
	const auto Collider = GetPlayerCharacter()->GetCapsuleComponent();

	// �L�����N�^�[��q�b�g�{�b�N�X���L�����ǂ������m�F
	if (!GetPlayerCharacter() || !Collider)
	{
		return false; // �����ȏꍇ��false��Ԃ�
	}

	// �L�����N�^�[�̈ʒu���擾
	FVector startPos = GetPlayerCharacter()->GetActorLocation();

	// �J�v�Z���̒ꕔ�ɊJ�n�ʒu�𒲐�
	startPos.Z -= Collider->GetScaledCapsuleHalfHeight();

	// �g���[�X�������`
	const float TraceDistance = 5.0f;

	// �I���ʒu���L�����N�^�[�̐^����TraceDistance�������ړ����Đݒ�
	FVector endPos = startPos - GetPlayerCharacter()->GetActorUpVector() * TraceDistance;

	// �Փ˃N�G���p�����[�^��ݒ肵�A�L�����N�^�[���g�𖳎�����悤�ɂ���
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetPlayerCharacter());

	// �f�o�b�O���C����`�悵�A�g���[�X�͈̔͂����o��
	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Green);

	// ���C���E�g���[�X�̌��ʂ��i�[���邽�߂�FHitResult�ϐ����`
	FHitResult outHit;

	// ���C���E�g���[�X�����s���āA�L�����N�^�[�̐^���ɏ�Q�������邩�ǂ������m�F
	GetWorld()->LineTraceSingleByChannel(outHit, startPos, endPos, ECC_WorldStatic, params);

	// �g���[�X���ʂ��`�F�b�N���āA�u���b�L���O�q�b�g�������true��Ԃ�
	if (outHit.bBlockingHit)
	{
		return true;
	}

	// �u���b�L���O�q�b�g���Ȃ����false��Ԃ�
	return false;
}


///////////////////////////FORCEINLINE
AA_GameMode* UA_MovementInput::GetGameMode() const
{
	return Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

AA_MainCamera* UA_MovementInput::GetMainCamera() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetMainCamera();
}

AA_Player* UA_MovementInput::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}