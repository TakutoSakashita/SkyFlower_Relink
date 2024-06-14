#include "SFA_GA_Combo2.h"

#include "SFA_EnemyBase.h"

void USFA_GA_Combo2::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Player))
	{
		Debug::PrintFixedLine("USFA_GA_Combo2 : PlayerNull", 222);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		Debug::PrintFixedLine("USFA_GA_Combo2 : CommitAbilityNull", 222);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FVector SourceLocation = Player->GetActorLocation();
	TArray<AActor*> PotentialTargets;
	// 例えば、すべての敵キャラクターを取得する
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFA_EnemyBase::StaticClass(), PotentialTargets);
	AActor* ClosestTarget = GetClosestActor(SourceLocation, PotentialTargets);
	
	if(ClosestTarget)
	{
		float DistanceToTarget = FVector::Dist(SourceLocation, ClosestTarget->GetActorLocation());
		if (DistanceToTarget < DistanceThreshold)
		{
			// 敵の方向を向く
			FRotator TargetRotation = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).Rotation();
			Player->SetActorRotation(TargetRotation);
		
			UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionConstantForce =
				UAbilityTask_ApplyRootMotionMoveToActorForce::ApplyRootMotionMoveToActorForce(
					this,
					FName("MoveToTarget"),
					ClosestTarget,
					FVector::ZeroVector,
					ERootMotionMoveToActorTargetOffsetType::AlignFromTargetToSource,
					MoveToTargetDuration,
					nullptr, // TargetLerpSpeedHorizontal
					nullptr, // TargetLerpSpeedVertical
					true, // bSetNewMovementMode
					EMovementMode::MOVE_Walking,
					true, // bRestrictSpeedToExpected
					nullptr, // PathOffsetCurve
					nullptr, // TimeMappingCurve
					ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity,
					FVector::ZeroVector, // SetVelocityOnFinish
					0.f, // ClampVelocityOnFinish
					false // bDisableDestinationReachedInterrupt
				);

			//ApplyRootMotionConstantForce->OnFinished.AddDynamic(this, &USFA_GA_Combo2::OnMoveCompleted);
			//OnTimedOut.AddDynamic(this, &USFA_GA_Combo2::OnMoveCompleted);
			//ApplyRootMotionConstantForce->OnTimedOutAndDestinationReached.AddDynamic(this, &USFA_GA_Combo2::OnMoveCompleted);

			ApplyRootMotionConstantForce->ReadyForActivation();
		}
	}

	UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this,
		FGameplayTag::RequestGameplayTag(FName("Ability.Begin.Combo2")),
		nullptr,
		false);

	if (Task)
	{
		Task->Added.AddDynamic(this, &USFA_GA_Combo2::HandleMyTagAdded);
		Task->ReadyForActivation();
	}
}

void USFA_GA_Combo2::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo,
                                bool bReplicateEndAbility,
                                bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo3"));
	RemoveGameplayTags(TagContainer);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo3"));
	RemoveGameplayTags(TagContainer);
}

AActor* USFA_GA_Combo2::GetClosestActor(const FVector& SourceLocation, TArray<AActor*> PotentialTargets)
{
	AActor* ClosestActor = nullptr;
	float MinDistance = FLT_MAX;

	for (AActor* Target : PotentialTargets)
	{
		if (Target)
		{
			float Distance = FVector::Dist(SourceLocation, Target->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestActor = Target;
			}
		}
	}

	return ClosestActor;
}

void USFA_GA_Combo2::HandleMyTagAdded()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleMyTagAdded"));

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance))
	{
		Debug::PrintFixedLine("USFA_GA_Combo2 : AnimInstanceNull", 222);
		return;
	}

	ASFA_Weapon* SFA_Weapon = Player->GetWeapon();
	if (!SFA_Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("SFA_Weapon :null"));
		return;
	}

	CollisionBoxComponent = SFA_Weapon->GetBoxComponent();
	if (!CollisionBoxComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBoxComponent :null"));
		return;
	}

	// �A�j���[�V�����Đ�
	AnimInstance->Montage_Play(AttackMontage);

	// �A�j���[�V�����֘A�̒ʒm
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo2::OnBlendOut);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo2::OnNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo2::OnNotifyEnd);
}

void USFA_GA_Combo2::OnBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBlendOut"));

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
	if (bInterrupted)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnInterrupted"));
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	// コリジョンを無効にする
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void USFA_GA_Combo2::OnNotifyBegin(FName NotifyName,
                                   const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo2::OnNotifyBegin", 222);

	if (!CollisionBoxComponent) return;

	if (NotifyName == "OnCollision")
	{
		// コリジョンを有効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	// NotifyName�ɉ������^�O�̒ǉ�
	if (NotifyName == nInput)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
		AddGameplayTags(TagContainer);
	}
	else if (NotifyName == nBranch)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
		AddGameplayTags(TagContainer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo2::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}

void USFA_GA_Combo2::OnNotifyEnd(FName NotifyName,
                                 const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo2::OnNotifyEnd", 222);

	if (!CollisionBoxComponent) return;

	if (NotifyName == "OnCollision")
	{
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// NotifyName�ɉ������^�O�̍폜
	if (NotifyName == nInput)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
		RemoveGameplayTags(TagContainer);
	}
	else if (NotifyName == nBranch)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
		RemoveGameplayTags(TagContainer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo2::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}

void USFA_GA_Combo2::OnMoveCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("OnMoveCompleted"));
}
