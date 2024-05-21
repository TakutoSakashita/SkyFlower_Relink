// ==================================================
// Filename	:	SF_MoveInput.cpp
// Author	:	22cu0115 坂下拓人
// Description: 移動の関数定義
// Notes:		例
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

	// 入力方向に移動
	m_pCharacter->AddMovementInput(GetMainCamera()->GetActorForwardVector(), InValue);

	// 回転
	CharacterRotate();
}

void USF_MovementInput::MoveRight(const float InValue)
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	// 入力方向に移動
	m_pCharacter->AddMovementInput(GetMainCamera()->GetActorRightVector(), InValue);

	// 回転
	CharacterRotate();
}

void USF_MovementInput::MoveDash()
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	//UE_LOG(LogTemp, Warning, TEXT(": %s"), *m_pCharacter->GetCharacterMovement()->Velocity.ToString());
	//Debug::Print(GetPlayerCharacter()->GetCharacterMovement()->Velocity.ToString());

	// このやり方だとキャラクターの保持しているベロシティの向きにだけダッシュするので
	// プレイヤーの向きを変えてもダッシュし続けているとその方向にしか動かない
	//// キャラクターの速度ベクトルを取得
	//FVector CharacterVelocity = GetPlayerCharacter()->GetCharacterMovement()->Velocity;
	//
	//// 速度ベクトルがゼロでないことを確認してから正規化
	//if (!CharacterVelocity.IsNearlyZero())
	//{
	//	CharacterVelocity.Normalize();
	//	AddForce(CharacterVelocity);
	//}

	// キャラクターとカメラの正面方向を足してその向きにダッシュするように
	AddForce(m_pCharacter->GetActorForwardVector());
}

void USF_MovementInput::MoveJump()
{
	//if (!IsValid(GetMainCamera())) return;
	if (!m_pCharacter) return;

	// 入力方向に移動
	//m_pCharacter->AddMovementInput(m_pCharacter->GetActorUpVector(), InValue);
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	m_pCharacter->GetCharacterMovement()->AddImpulse(m_pCharacter->GetActorUpVector() * dashSpeed, true);
}

void USF_MovementInput::AddForce(const FVector InDirection)
{
	// プレイヤーの速度を０にする
	m_pCharacter->GetCharacterMovement()->Velocity = FVector::Zero();
	// ダッシュ
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	m_pCharacter->GetCharacterMovement()->AddImpulse(InDirection * dashSpeed, true);
}

void USF_MovementInput::CharacterRotate() const
{
	if (!m_pCharacter) return;

	const FVector movement = m_pCharacter->GetLastMovementInputVector();

	// 入力がある時だけ回転
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