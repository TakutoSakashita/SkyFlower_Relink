// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_ShootState.h"
#include "SFA_Bullet.h"
#include "Asterisk/DebugHelpers.h"
#include "../DebugHelpers.h"

void USFA_ShootState::OnEnterState()
{
	Super::OnEnterState();

	//calculate bullet direction
	FVector CameraPos = Camera->GetCameraCompLocation();
	FVector CameraDir = Camera->GetCameraCompForwardVector();
	FVector LineTraceEndDir = CameraPos + CameraDir * 50000.0f /* lineTrace length */;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Camera);
	CollisionParams.AddIgnoredActor(Player);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraPos, LineTraceEndDir, ECC_Visibility,
	                                                 CollisionParams);

	FVector BulletDirEnd;
	if (bHit)
	{
		BulletDirEnd = HitResult.Location;
	}
	else
	{
		BulletDirEnd = LineTraceEndDir;
	}

	FVector PlayerRightHandDir = Player->GetMesh()->GetSocketLocation(TEXT("RightHandMiddle1"));
	FVector BulletDir = (BulletDirEnd - PlayerRightHandDir).GetSafeNormal(); // Dir = End - Start

	//DRAW_SPHERE(PlayerRightHandDir)
	//DRAW_VECTOR(CameraPos, BulletDestination)

	//spawn bullet
	if (BulletClass)
	{
		FTransform Transform;
		ASFA_Bullet* Bullet = GetWorld()->SpawnActorDeferred<ASFA_Bullet>(BulletClass, Transform);
		if (Bullet)
		{
			if (PlayerStateMachine->bIsAiming)
			{
				Transform.SetScale3D(FVector(2.f, 2.f, 2.f));
				Bullet->SetBulletSpeed(10000.f);
			}
			Transform.SetLocation(PlayerRightHandDir);
			Bullet->Initialize(BulletDir, Player);
			//Bullet->Damage = 10.f;
			UGameplayStatics::FinishSpawningActor(Bullet, Transform);
		}
	}

	// play montage
	if (ShootMontage)
		Player->GetMesh()->GetAnimInstance()->Montage_Play(ShootMontage);

	// play sound
	if (ShootSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, PlayerRightHandDir, FRotator::ZeroRotator);

	// play effect
	if (ShootEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootEffect, PlayerRightHandDir, FRotator::ZeroRotator,
		                                         FVector(3));
}

void USFA_ShootState::TickState(float DeltaTime)
{
	//exit state when montage is over
	if (!ShootMontage) return;
	if (UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance())
	{
		if (!AnimInstance->Montage_IsPlaying(ShootMontage))
		{
			//TODO back to pre-state
			PlayerStateMachine->SwitchStateByKey("Float");
		}
	}
}

void USFA_ShootState::OnExitState()
{
	Super::OnExitState();
}
