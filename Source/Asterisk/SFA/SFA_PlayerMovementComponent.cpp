// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_PlayerMovementComponent.h"
#include "SFA_Player.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
//debug
#include "../DebugHelpers.h"

USFA_PlayerMovementComponent::USFA_PlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	GravityScale = 2.f;
	MaxFlySpeed = 1600.f;
	JumpZVelocity = 1600.f;
}


// Called when the game starts
void USFA_PlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ASFA_Player>(GetOwner());
	AnimInstance = CharacterOwner->GetMesh()->GetAnimInstance();
	
}


// Called every frame
void USFA_PlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MovementMode == EMovementMode::MOVE_Flying && CheckHasReachedFloor()) {
		Debug::PrintFixedLine("HAS REACHED FLOOR", 222);
		if (MovementMode == EMovementMode::MOVE_Flying) {
			SetMovementMode(MOVE_Falling);
			GravityScale = 2.f;
			//todo playMontage
		}
	}
}

void USFA_PlayerMovementComponent::UpdateForce(float DeltaTime)
{
	if (!bForce)return;

	// 移動量
	forceValue -= /*forceDecelerationValue*/ 20.f * DeltaTime;
	FVector forceDirection;
	Velocity.Z == 0.f ? forceDirection = Player->GetActorUpVector() : Player->GetActorForwardVector();

	// 力を受けてなかったら無視
	if (forceValue <= Velocity.Size())
	{
		bForce = false;
		return;
	}

	// 移動
	SweepMove(forceDirection, forceValue);
}

void USFA_PlayerMovementComponent::SweepMove(FVector MoveVector, float MoveSpeed)
{
	// 座標算出
	FVector MovePos = Player->GetActorLocation();
	MovePos += MoveVector * MoveSpeed;
	FHitResult outHit;
	Player->SetActorLocation(MovePos, true, &outHit);	
}

TArray<FHitResult> USFA_PlayerMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape, bool bDrawPersistentShapes)
{
	TArray<FHitResult> OutCapsuleTranceHitResults;

	EDrawDebugTrace::Type DebugTraceType = EDrawDebugTrace::None;

	if (bShowDebugShape)
	{
		DebugTraceType = EDrawDebugTrace::ForOneFrame;

		if (bDrawPersistentShapes)
		{
			DebugTraceType = EDrawDebugTrace::Persistent;
		}
	}

	UKismetSystemLibrary::CapsuleTraceMultiForObjects(
		this,
		Start,
		End,
		40.f /*ClimbCapsuleTraceRadius*/,
		60.f /*ClimbCapsuleTraceHalfHeight*/,
		SurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		DebugTraceType,
		OutCapsuleTranceHitResults,
		true
	);

	return OutCapsuleTranceHitResults;
}

bool USFA_PlayerMovementComponent::CheckHasReachedFloor()
{
	const FVector DownVector = -UpdatedComponent->GetUpVector();
	const FVector StartOffset = DownVector * 150.f/*FloorCheckDistance*/;

	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
	const FVector End = Start + DownVector;

	TArray<FHitResult> PossibleFloorHits = DoCapsuleTraceMultiByObject(Start, End);

	if (PossibleFloorHits.IsEmpty()) return false;

	FVector UnrotatedClimbVelocity =
		UKismetMathLibrary::Quat_UnrotateVector(UpdatedComponent->GetComponentQuat(), Velocity);

	for (const FHitResult& PossibleFloorHit : PossibleFloorHits)
	{
		const bool bFloorReached =
			FVector::Parallel(-PossibleFloorHit.ImpactNormal, FVector::UpVector) &&
			UnrotatedClimbVelocity.Z < -10.f;	/* moving down */

		if (bFloorReached) return true;
	}

	return false;
}

