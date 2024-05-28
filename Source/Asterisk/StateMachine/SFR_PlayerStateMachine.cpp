// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerStateMachine.h"
#include "../SFR/SFR_InputHandlerComponent.h"
#include "../SFR/SFR_PlayerController.h"
#include "../SFR/SFR_Camera.h"
#include "../SFR/SFR_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

#include "../DebugHelpers.h"

#define TIME UGameplayStatics::GetGlobalTimeDilation(GetWorld())

USFR_PlayerStateMachine::USFR_PlayerStateMachine()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USFR_PlayerStateMachine::Initialize(ASFR_Player* player)
{
	PlayerRef = player;
	InputHandler = player->GetInputHandler();
	CameraRef = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
}


void USFR_PlayerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateRootMotion(DeltaTime);
	UpdateMove(DeltaTime);
	//UpdateGravity(DeltaTime);

	UpdateForce(DeltaTime);
	UpdateRotation(DeltaTime);//update player rotation to move direction
}

void USFR_PlayerStateMachine::AddForwardMovementInput(float InputValue)
{
	if (InputValue == 0.f)
	{
		bInputFwd = false;
		if (inputBias.Y >= 0)
			inputBias.Y = FMath::Clamp(inputBias.Y - stopPower, 0, inputBias.Y);
		else
			inputBias.Y = FMath::Clamp(inputBias.Y + stopPower, inputBias.Y, 0);
	}
	else
	{
		bInputFwd = true;
		inputBias.Y = FMath::Clamp(inputBias.Y + InputValue * airControll, -1, 1); //
	}
	inputValue.Y = InputValue;
}

void USFR_PlayerStateMachine::AddRightMovementInput(float InputValue)
{
	// 入力が無ければ０に補正していく
	if (InputValue == 0.f)
	{
		bInputRight = false;
		if (inputBias.X >= 0)
			inputBias.X = FMath::Clamp(inputBias.X - stopPower, 0, inputBias.X);
		else
			inputBias.X = FMath::Clamp(inputBias.X + stopPower, inputBias.X, 0);
	}
	else
	{
		bInputRight = true;
		inputBias.X = FMath::Clamp(inputBias.X + InputValue * airControll, -1, 1); //
	}
	inputValue.X = InputValue;
}

void USFR_PlayerStateMachine::UpdateRootMotion(float DeltaTime)
{
	USkeletalMeshComponent* mesh = PlayerRef->GetMesh();
	FRootMotionMovementParams params = mesh->GetAnimInstance()->ConsumeExtractedRootMotion(1.0f);
	if (!params.bHasRootMotion)
	{
		bRootMotion = false;
		return;
	}

	// RootMotionの使用可否
	//if (!PlayerRef->AbilityComp()->ActiveAbility().bUseRootMotionInAir) return;
	//bRootMotion = true;

	// TakeAction中のみ
	//if (!PlayerRef->IsTakingAction())return;

	// 移動
	FHitResult* outHit = nullptr;
	FTransform tr = mesh->ConvertLocalRootMotionToWorld(params.GetRootMotionTransform());
	PlayerRef->AddActorWorldTransform(tr, true, outHit);

	if (outHit->bBlockingHit)
	{
		// ルートモーション中に上に乗れちゃうことがある問題直したい
		FVector vec = FVector::ZeroVector;
	}
}

void USFR_PlayerStateMachine::UpdateMove(float DeltaTime)
{
	if (IsValid(CameraRef))
	{
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0).GetSafeNormal();
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0).GetSafeNormal();
		FVector2D V = inputBias;
		V.Normalize();
		FVector MoveDirection = Fwd * FMath::Abs(V.Y) * inputBias.Y + Right * FMath::Abs(V.X) * inputBias.X;

		SweepMove(MoveDirection, moveSpeed * moveSpeedBias * TIME);

		Debug::PrintFixedLine(" moveSpeed : " + LexToString(moveSpeed) + " moveSpeedBias : " + LexToString(moveSpeedBias), 10);
	}
}

void USFR_PlayerStateMachine::UpdateForce(float DeltaTime)
{
	if (!bForce)return;

	// 移動量
	forceValue -= forceDecelerationValue * DeltaTime;
	FVector forceDirection = forceVector;

	// 力を受けてなかったら無視
	if (/*forceValue <= 0*/forceValue * TIME <= moveSpeed * moveSpeedBias * TIME)
	{
		bForce = false;
		if (bGlide)return;
		//if (bFly)return;
		ResetGravityBias();
		ResetAirbornTime();
		ResetSpeedBias();

		InputHandler->InputState = EInputState::Both_enable;

		return;
	}

	// 移動
	SweepMove(forceDirection, forceValue * TIME);
}

void USFR_PlayerStateMachine::UpdateRotation(float DeltaTime)
{
	// 入力してないときは回転しない
	if (!bInputFwd && !bInputRight)return;

	if (IsValid(CameraRef))
	{
		// カメラベクトル
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0);
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0);
		// 移動方向
		FVector MoveVelocity = Fwd * inputValue.Y + Right * inputValue.X;
		// 回転
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(PlayerRef->GetActorLocation(), PlayerRef->GetActorLocation() + MoveVelocity);
		PlayerRef->SetActorRotation(rotation);
	}
}

bool USFR_PlayerStateMachine::SweepMove(FVector MoveVector, float MoveSpeed)
{
	// 座標算出
	FVector MovePos = PlayerRef->GetActorLocation();
	MovePos += MoveVector * MoveSpeed;
	// 移動
	FHitResult outHit;
	PlayerRef->SetActorLocation(MovePos, true, &outHit);
	if (outHit.bBlockingHit)
	{
		// 壁に当たったら壁ずりベクトルに移動
		FVector v = FVector(MoveVector.X, MoveVector.Y, MoveVector.Z);
		v.Normalize();
		FVector alongWallVector = GetAlongWallVector(outHit.Normal, v);
		MovePos = PlayerRef->GetActorLocation();
		MovePos += alongWallVector * MoveVector.Length() * MoveSpeed;
		PlayerRef->SetActorLocation(MovePos, true, &outHit);
		DrawDebugLine(GetWorld(), outHit.ImpactPoint, outHit.ImpactPoint + outHit.Normal * 500.f, FColor::Red);
		DrawDebugLine(GetWorld(), PlayerRef->GetActorLocation(), PlayerRef->GetActorLocation() + alongWallVector * 500.f, FColor::Green);
	}
	return outHit.bBlockingHit;
}

FVector USFR_PlayerStateMachine::GetAlongWallVector(FVector_NetQuantizeNormal HitNormal, FVector MoveVector)
{
	// 壁ずりベクトルを算出
// w = f - Dot(f,n) ・ n
	float dot = (MoveVector.X * HitNormal.X + MoveVector.Y * HitNormal.Y + MoveVector.Z * HitNormal.Z) /
		(FMath::Sqrt(MoveVector.X * MoveVector.X + MoveVector.Y * MoveVector.Y + MoveVector.Z * MoveVector.Z) *
			FMath::Sqrt(HitNormal.X * HitNormal.X + HitNormal.Y * HitNormal.Y + HitNormal.Z * HitNormal.Z));
	FVector alongWallVector = MoveVector - dot * HitNormal;

	return alongWallVector;
}

bool USFR_PlayerStateMachine::UnderCheck()
{
	FVector startPos = PlayerRef->GetActorLocation();
	startPos.Z -= PlayerRef->GetCapsule()->GetScaledCapsuleHalfHeight();
	FVector endPos = startPos - PlayerRef->GetActorUpVector() * 5.f/*lineTrace length*/;
	FCollisionQueryParams params;
	params.AddIgnoredActor(PlayerRef);

	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Green);

	FHitResult outHit;
	GetWorld()->LineTraceSingleByChannel(outHit, startPos, endPos, ECC_WorldStatic, params);
	if (outHit.bBlockingHit)
	{
		return true;
	}
	return false;
}

void USFR_PlayerStateMachine::AddForce(FVector Vector, float Value, float Deceleration)
{

	Vector.Normalize();
	forceVector = Vector;
	forceValue = Value;
	forceDecelerationValue = Deceleration;
	bForce = true;

	beforeGravityAcceleration = 0;
	ResetAirbornTime();
	ResetGravityBias();
	ResetSpeedBias();
}


