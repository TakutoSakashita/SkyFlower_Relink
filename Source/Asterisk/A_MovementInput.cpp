#include "A_MovementInput.h"
#include "A_GameMode.h"
#include "A_Player.h"
#include "A_MainCamera.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DebugHelpers.h"
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

	m_pCharacter = Cast<AA_Player>(GetOwner());
	ensure(m_pCharacter != nullptr);
	m_pMainCamera = Cast<AA_MainCamera>(GetOwner());
	ensure(m_pCharacter != nullptr);
}

void UA_MovementInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	// ルートモーション
	//UpdateRootMosion(DeltaTime);
	// 移動
	//UpdateMove(DeltaTime);
	
	// 飛翔
	UpdateFly(DeltaTime);
	// 重力
	UpdateGravity(DeltaTime);

	if (GetPlayerCharacter()->GetCharacterState() == ESF_CharacterState::Fly)
	{
		if (!AnimInstance->Montage_IsPlaying(ComboMontage))
		{
			GetPlayerCharacter()->PlayAnimMontage(ComboMontage, 1.0f, "Fly");
		}
	}
}

void UA_MovementInput::MoveForward(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	// 入力方向に移動
	m_pCharacter->AddMovementInput(GetMainCamera()->GetActorForwardVector(), InValue);

	// 回転
	CharacterRotate();
}

void UA_MovementInput::MoveAcceleration(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	//GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = MaxAcceleration;
}

void UA_MovementInput::MoveRight(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	// 入力方向に移動
	m_pCharacter->AddMovementInput(GetMainCamera()->GetActorRightVector(), InValue);

	// 回転
	CharacterRotate();
}

void UA_MovementInput::MoveDash()
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::Fly);

	// キャラクターとカメラの正面方向を足してその向きにダッシュするように
	AddForce(GetPlayerCharacter()->GetActorForwardVector());

	GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = MaxAcceleration;
	
	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	GetPlayerCharacter()->PlayAnimMontage(ComboMontage, 1.0f, "Fly");
	
}

void UA_MovementInput::StopMoveDash()
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::Normal);
	
	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	GetPlayerCharacter()->GetCharacterMovement()->MaxFlySpeed = InitAcceleration;
	AnimInstance->Montage_Stop(0.2f,ComboMontage);
}

void UA_MovementInput::MoveJump()
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

	m_pCharacter->GetCharacterMovement()->Velocity = FVector::Zero();

	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();

	if (!AnimInstance->Montage_IsPlaying(ComboMontage))
	{
		GetPlayerCharacter()->PlayAnimMontage(ComboMontage, 1.0f, "Avoid");
	}

	// 入力方向に移動
	//m_pCharacter->AddMovementInput(m_pCharacter->GetActorUpVector(), InValue);
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	m_pCharacter->GetCharacterMovement()->AddImpulse(m_pCharacter->GetActorUpVector() * dashSpeed, true);
}

void UA_MovementInput::AddForce(const FVector InDirection)
{
	// プレイヤーの速度を０にする
	m_pCharacter->GetCharacterMovement()->Velocity = FVector::Zero();
	// ダッシュ
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	m_pCharacter->GetCharacterMovement()->AddImpulse(InDirection * dashSpeed, true);
}

void UA_MovementInput::CharacterRotate() const
{
	if (!GetPlayerCharacter()) return;
	if (!GetMainCamera()) return;

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

/// @brief 重力更新
/// @param DeltaTime 
void UA_MovementInput::UpdateGravity(float DeltaTime)
{
	GetMainCamera()->SetViewPoint(GetPlayerCharacter()->GetActorLocation());

	// 浮遊中
	//if (GetPlayerCharacter()->GetCharacterState() == ESF_CharacterState::Float) return;
	
	float gravityAcceleration = 0;
	
	// 飛翔中
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
	
	// 落下速度を保存
	beforeGravityAcceleration = gravityAcceleration;

	////速度制限::後々ダイビングモードとかに変更するヨ
	//if (beforeGravityAcceleration > FallingSpeedLimit) {
	//	beforeGravityAcceleration = FallingSpeedLimit;
	//}

	// 移動
	GetPlayerCharacter()->SetActorLocation(GetPlayerCharacter()->GetActorLocation() + 
		FVector(0, 0, -1) * beforeGravityAcceleration);
}

/// @brief 加速
/// @param DeltaTime
void UA_MovementInput::UpdateFly(float DeltaTime)
{
	if (!bFly)return;

	//// 方向取得
	//AGSFCamera* camera = Cast<AGSFGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->camera;
	//if (IsValid(camera))
	//{
	//	// カメラベクトル
	//	FVector Fwd = FVector(camera->arrow->GetForwardVector().X, camera->arrow->GetForwardVector().Y, 0);
	//	FVector Right = FVector(camera->arrow->GetRightVector().X, camera->arrow->GetRightVector().Y, 0);
	//	// 移動方向
	//	if (inputValue.IsZero())
	//	{
	//		flyVec = character->GetActorForwardVector();
	//	}
	//	else
	//	{
	//		FVector2D V = inputBias;
	//		V.Normalize();
	//		flyVec = Fwd * FMath::Abs(V.Y) * inputBias.Y + Right * FMath::Abs(V.X) * inputBias.X;
	//		//flyVec = Fwd * inputValue.Y + Right * inputValue.X;
	//	}

	//	//flyVec = camera->arrow->GetForwardVector();
	//	flyVec.Z = 0.f;
	//}

	//flyVec.Z = flyZVelocity * flyCurveZ->GetFloatValue(flyDurationTimer);
	//currentFlyVelocityValue = flyVelocityValue * flyCurveSpeed->GetFloatValue(flyDurationTimer);

	//DrawDebugLine(GetWorld(), character->GetActorLocation(), character->GetActorLocation() + flyVec * 300.f, FColor::Blue);

	//// 時間
	//flyDurationTimer += DeltaTime;
	//if (flyDurationTimer > flyDuration)
	//{
	//	bFly = false;
	//	ResetAirbornTime();
	//	ResetGravityBias();
	//	ResetSpeedBias();

	//	if (IsValid(camera))
	//	{
	//		camera->ResetBoomLength();
	//	}
	//	return;
	//}

	//// 移動
	//SweepMove(flyVec, currentFlyVelocityValue * TIME);
}

bool UA_MovementInput::UnderCheck()
{
	const auto Collider = GetPlayerCharacter()->GetCapsuleComponent();

	// キャラクターやヒットボックスが有効かどうかを確認
	if (!GetPlayerCharacter() || !Collider)
	{
		return false; // 無効な場合はfalseを返す
	}
	
	// キャラクターの位置を取得
	FVector startPos = GetPlayerCharacter()->GetActorLocation();
	
	// カプセルの底部に開始位置を調整
	startPos.Z -= Collider->GetScaledCapsuleHalfHeight();
	
	// トレース距離を定義
	const float TraceDistance = 5.0f;
	
	// 終了位置をキャラクターの真下にTraceDistance分だけ移動して設定
	FVector endPos = startPos - GetPlayerCharacter()->GetActorUpVector() * TraceDistance;
	
	// 衝突クエリパラメータを設定し、キャラクター自身を無視するようにする
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetPlayerCharacter());
	
	// デバッグラインを描画し、トレースの範囲を視覚化
	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Green);
	
	// ライン・トレースの結果を格納するためのFHitResult変数を定義
	FHitResult outHit;
	
	// ライン・トレースを実行して、キャラクターの真下に障害物があるかどうかを確認
	GetWorld()->LineTraceSingleByChannel(outHit, startPos, endPos, ECC_WorldStatic, params);
	
	// トレース結果をチェックして、ブロッキングヒットがあればtrueを返す
	if (outHit.bBlockingHit)
	{
		return true;
	}
	
	// ブロッキングヒットがなければfalseを返す
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