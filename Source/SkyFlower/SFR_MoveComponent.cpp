// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_MoveComponent.h"
#include "SFR_InputHandlerComponent.h"
#include "DebugHelpers.h"
#include "SFR_PlayerController.h"
#include "SFR_PlayerCamera.h"
#include "SFR_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

#define TIME UGameplayStatics::GetGlobalTimeDilation(GetWorld())

USFR_MoveComponent::USFR_MoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USFR_MoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void USFR_MoveComponent::SwitchStateByKey(FString StateKey)
{
	Super::SwitchStateByKey(StateKey);
}

void USFR_MoveComponent::InitStateManager()
{
	Super::InitStateManager();
}

void USFR_MoveComponent::InitializeStates()
{
	Super::InitializeStates();
}

void USFR_MoveComponent::Initialize(ASFR_Player* player)
{
	PlayerRef = player;
	InputHandler = player->GetInputHandler();
	CameraRef = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
}


// Called every frame
void USFR_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateRootMotion(DeltaTime);
	UpdateMove(DeltaTime);
	//UpdateGravity(DeltaTime);

	UpdateForce(DeltaTime);
	//UpdateFly(DeltaTime);
	UpdateRotation(DeltaTime);//update player rotation to move direction
}

//void USFR_MoveComponent::MoveForward(float Value)
//{
//	if (!IsValid(PlayerRef)) return;
//	if (!IsValid(CameraRef)) return;
//	const FVector Direction = FRotationMatrix(CameraRef->GetActorRotation()).GetScaledAxis(EAxis::X);
//	FVector Offset = Direction * Value * (/*CurrentVelocity*/ CurrentVelocity * /*DeltaTime*/ 1.f);
//	PlayerRef->AddActorWorldOffset(Offset);
//
//	if (bDebugLog)
//		Debug::PrintFixedLine("ASFR_PlayerCamera::MoveForward  " + Direction.ToString(), 110);
//}

//void USFR_MoveComponent::MoveRight(float Value)
//{
//	if (!IsValid(PlayerRef)) return;
//	if (!IsValid(CameraRef)) return;
//	const FVector Direction = FRotationMatrix(CameraRef->GetActorRotation()).GetScaledAxis(EAxis::Y);
//	FVector Offset = Direction * Value * (/*CurrentVelocity*/ CurrentVelocity * /*DeltaTime*/ 1.f);
//	PlayerRef->AddActorWorldOffset(Offset);
//	if (bDebugLog)
//		Debug::PrintFixedLine("ASFR_PlayerCamera::MoveRight  " + Direction.ToString(), 120);
//}



void USFR_MoveComponent::AddForwardMovementInput(float InputValue)
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

void USFR_MoveComponent::AddRightMovementInput(float InputValue)
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


void USFR_MoveComponent::UpdateRootMotion(float DeltaTime)
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

void USFR_MoveComponent::UpdateMove(float DeltaTime)
{

	if (IsValid(CameraRef))
	{
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0).GetSafeNormal();
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0).GetSafeNormal();
		FVector2D V = inputBias;
		V.Normalize();
		FVector MoveVelocity = Fwd * FMath::Abs(V.Y) * inputBias.Y + Right * FMath::Abs(V.X) * inputBias.X;

		SweepMove(MoveVelocity, moveSpeed * moveSpeedBias * TIME);

		Debug::PrintFixedLine(" moveSpeed : " + LexToString(moveSpeed) + " moveSpeedBias : " + LexToString(moveSpeedBias), 10);
	}

}

//void USFR_MoveComponent::UpdateGravity(float DeltaTime)
//{
//	// Wire移動中
//	if (bWire)return;
//	// 浮遊中
//	if (bFloat) return;
//	// 吹っ飛び中
//	if (bForce)return;
//	// 飛翔中
//	if (bFly)return;
//	// 怯み中
//	if (character->bInFear)return;
//
//	float gravityAcceleration = 0;
//	if (UnderCheck())
//	{
//		airborneTime = 0;
//		gravityAcceleration = 0.f;
//		//bDive = false;
//		if (!bGlide)
//		{
//			ResetSpeedBias();
//	
//			if (IsValid(CameraRef))
//			{
//				CameraRef->ResetBoomLength();
//				CameraRef->ResetPitch();
//			}
//		}
//	}
//	else
//	{
//		airborneTime += DeltaTime;
//		if (airborneTime >= diveThreshold && !bGlide)
//		{
//			bDive = true;
//			gravityAcceleration = diveGravity;
//			SetDiveSpeedBias();
//			UE_LOG(LogTemp, Log, TEXT("Dive : moveComp : UpdateGravity"));
//
//			
//			if (IsValid(CameraRef))
//			{
//				CameraRef->SetDiveBoomLength();
//				CameraRef->SetDivePitch();
//			}
//		}
//		else
//		{
//			//bDive = false;
//			gravityAcceleration = 0.5f * gravity * gravityBias * pow(airborneTime, 2) * TIME;
//
//			if (!bGlide)
//			{
//				ResetSpeedBias();
//				if (IsValid(CameraRef))
//				{
//					CameraRef->ResetBoomLength();
//					CameraRef->ResetPitch();
//				}
//			}
//		}
//	}
//}



void USFR_MoveComponent::UpdateForce(float DeltaTime)
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

//void USFR_MoveComponent::UpdateFly(float DeltaTime)
//{
	//if (!bFly)return;
	//
	//if (IsValid(CameraRef))
	//{
	//	// カメラベクトル
	//	FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0);
	//	FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0);
	//	// 移動方向
	//	if (inputValue.IsZero())
	//	{
	//		flyVec = PlayerRef->GetActorForwardVector();
	//	}
	//	else
	//	{
	//		FVector2D V = inputBias;
	//		V.Normalize();
	//		flyVec = Fwd * FMath::Abs(V.Y) * inputBias.Y + Right * FMath::Abs(V.X) * inputBias.X;
	//		//flyVec = Fwd * inputValue.Y + Right * inputValue.X;
	//	}
	//
	//	//flyVec = camera->arrow->GetForwardVector();
	//	flyVec.Z = 0.f;
	//}
	//
	//flyVec.Z = flyZVelocity * flyCurveZ->GetFloatValue(flyDurationTimer);
	//currentFlyVelocityValue = flyVelocityValue * flyCurveSpeed->GetFloatValue(flyDurationTimer);
	//
	//DrawDebugLine(GetWorld(), PlayerRef->GetActorLocation(), PlayerRef->GetActorLocation() + flyVec * 300.f, FColor::Blue);
	//
	//// 時間
	//flyDurationTimer += DeltaTime;
	//if (flyDurationTimer > flyDuration)
	//{
	//	bFly = false;
	//	ResetAirbornTime();
	//	ResetGravityBias();
	//	ResetSpeedBias();
	//
	//	if (IsValid(CameraRef))
	//	{
	//		CameraRef->ResetBoomLength();
	//	}
	//	return;
	//}
	//
	//// 移動
	//SweepMove(flyVec, currentFlyVelocityValue * TIME);
//}

void USFR_MoveComponent::UpdateRotation(float DeltaTime)
{
	// 飛翔中は自動
	//if (bFly)
	//{
	//	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(PlayerRef->GetActorLocation(), PlayerRef->GetActorLocation() + flyVec);
	//	FRotator rotation = CameraRef->GetActorRotation();
	//	PlayerRef->SetActorRotation(rotation);
	//	return;
	//}

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

bool USFR_MoveComponent::SweepMove(FVector MoveVector, float MoveSpeed)
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

FVector USFR_MoveComponent::GetAlongWallVector(FVector_NetQuantizeNormal HitNormal, FVector MoveVector)
{
	// 壁ずりベクトルを算出
	// w = f - Dot(f,n) ・ n
	float dot = (MoveVector.X * HitNormal.X + MoveVector.Y * HitNormal.Y + MoveVector.Z * HitNormal.Z) /
		(FMath::Sqrt(MoveVector.X * MoveVector.X + MoveVector.Y * MoveVector.Y + MoveVector.Z * MoveVector.Z) *
			FMath::Sqrt(HitNormal.X * HitNormal.X + HitNormal.Y * HitNormal.Y + HitNormal.Z * HitNormal.Z));
	FVector alongWallVector = MoveVector - dot * HitNormal;

	return alongWallVector;
}

bool USFR_MoveComponent::UnderCheck()
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

void USFR_MoveComponent::AddForce(FVector Vector, float Value, float Deceleration)
{
	//InputHandler->InputState = EInputState::Move_disable;


	Vector.Normalize();
	forceVector = Vector;
	forceValue = Value;
	forceDecelerationValue = Deceleration;
	bForce = true;

	// 吹き飛び以外の挙動をキャンセル
	//bFly = false;
	//bWire = false;
	//bDive = false;
	beforeGravityAcceleration = 0;
	//currentWireMoveTime = 0;
	ResetAirbornTime();
	ResetGravityBias();
	ResetSpeedBias();
}