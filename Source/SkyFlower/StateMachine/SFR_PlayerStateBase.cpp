// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"

#define TIME UGameplayStatics::GetGlobalTimeDilation(GetWorld())

void USFR_PlayerStateBase::OnEnterState()
{
	Super::OnEnterState();

	CameraRef = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	PlayerRef = Cast<ASFR_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(PlayerRef)) {
		InputHandlerRef = PlayerRef->InputHandler;
		MoveComponent = PlayerRef->MoveComponent;
	}

}

void USFR_PlayerStateBase::UpdateRootMotion(float DeltaTime)
{
}

void USFR_PlayerStateBase::UpdateMove(float DeltaTime)
{
	if (IsValid(CameraRef))
	{
		FVector Fwd = FVector(CameraRef->GetActorForwardVector().X, CameraRef->GetActorForwardVector().Y, 0);
		FVector Right = FVector(CameraRef->GetActorRightVector().X, CameraRef->GetActorRightVector().Y, 0);
		//FVector2D V = inputBias;
		//V.Normalize();
		FVector MoveVelocity = Fwd /** FMath::Abs(V.Y) * inputBias.Y*/ + Right /** FMath::Abs(V.X) * inputBias.X*/;

		SweepMove(MoveVelocity, moveSpeed * moveSpeedBias * TIME);
	}
}

void USFR_PlayerStateBase::UpdateForce(float DeltaTime)
{
}

void USFR_PlayerStateBase::UpdateFly(float DeltaTime)
{
}

void USFR_PlayerStateBase::UpdateGravity(float DeltaTime)
{
}

void USFR_PlayerStateBase::UpdateRotation(float DeltaTime)
{
}


bool USFR_PlayerStateBase::SweepMove(FVector MoveVector, float MoveSpeed)
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

FVector USFR_PlayerStateBase::GetAlongWallVector(FVector_NetQuantizeNormal HitNormal, FVector MoveVector)
{
	// 壁ずりベクトルを算出
	// w = f - Dot(f,n) ・ n
	float dot = (MoveVector.X * HitNormal.X + MoveVector.Y * HitNormal.Y + MoveVector.Z * HitNormal.Z) /
		(FMath::Sqrt(MoveVector.X * MoveVector.X + MoveVector.Y * MoveVector.Y + MoveVector.Z * MoveVector.Z) *
			FMath::Sqrt(HitNormal.X * HitNormal.X + HitNormal.Y * HitNormal.Y + HitNormal.Z * HitNormal.Z));
	FVector alongWallVector = MoveVector - dot * HitNormal;

	return alongWallVector;
}