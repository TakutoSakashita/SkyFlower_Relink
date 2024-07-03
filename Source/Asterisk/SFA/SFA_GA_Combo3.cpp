// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_GA_Combo3.h"

USFA_GA_Combo3::USFA_GA_Combo3()
{
	// Ability Tags（能力タグ）を設定
	this->AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Action.Attack")));
	// Activation Owned Tags（所有しているタグ）を設定
	this->ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.State.Combo3")));
	// Activation Required Tags（必要なタグ）を設定
	this->ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Ready.Combo3")));
}

void USFA_GA_Combo3::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Player)) return;

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;
	CommitAbility(Handle, ActorInfo, ActivationInfo);

	FVector SourceLocation = Player->GetActorLocation();
	TArray<AActor*> PotentialTargets;
	// 例えば、すべての敵キャラクターを取得する
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFA_EnemyBase::StaticClass(), PotentialTargets);

	if (AActor* ClosestTarget = GetClosestActor(SourceLocation, PotentialTargets))
	{
		float DistanceToTarget = FVector::Dist(SourceLocation, ClosestTarget->GetActorLocation());
		if (DistanceToTarget < DistanceThreshold)
		{
			// 敵の方向を向く
			FRotator TargetRotation = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).Rotation();
			Player->SetActorRotation(TargetRotation);

			// 敵から理想的な距離に位置するターゲットオフセットを計算
			FVector DirectionToTarget = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).
				GetSafeNormal();
			FVector TargetLocationOffset = DirectionToTarget * DesiredDistance;

			UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionConstantForce =
				UAbilityTask_ApplyRootMotionMoveToActorForce::ApplyRootMotionMoveToActorForce(
					this,
					FName("MoveToTarget"),
					ClosestTarget,
					TargetLocationOffset,
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
			ApplyRootMotionConstantForce->ReadyForActivation();
		}
	}

	if (UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this,
		FGameplayTag::RequestGameplayTag(FName("Ability.Begin.Combo3")),
		nullptr,
		false))
	{
		UE_LOG(LogTemp, Warning, TEXT("Task"));
		// �^�O���ǉ����ꂽ�Ƃ��̏�����ݒ�
		Task->Added.AddDynamic(this, &USFA_GA_Combo3::HandleMyTagAdded);
		Task->ReadyForActivation();
	}
}

void USFA_GA_Combo3::EndAbility(
	const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo4"));
	RemoveGameplayTags(TagContainer);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo4"));
	RemoveGameplayTags(TagContainer);
}

AActor* USFA_GA_Combo3::GetClosestActor(const FVector& SourceLocation, TArray<AActor*> PotentialTargets)
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

void USFA_GA_Combo3::HandleMyTagAdded()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleMyTagAdded"));

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance))
	{
		Debug::PrintFixedLine("USFA_GA_Combo3 : AnimInstanceNull", 222);
		return;
	};

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
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo3::OnBlendOut);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo3::OnNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo3::OnNotifyEnd);
}

void USFA_GA_Combo3::OnBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void USFA_GA_Combo3::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo3::OnNotifyBegin", 222);
	UE_LOG(LogTemp, Warning, TEXT("OnBlendOut"));

	if (!CollisionBoxComponent) return;

	if (NotifyName == "OnCollision")
	{
		// コリジョンを有効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	//OnNotifyBegin���Ă΂ꂽ���ɂ�Notify�Ή�����^�O��ǉ����A
	//RemoveGameplayTags���Ă΂ꂽ���ɂ�Notify�ɑΉ�����^�O�������B
	//Combo1.Input �� Ability.Ready.Combo2
	//Combo1.Branch �� Ability.Begin.Combo2
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
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo1::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}

void USFA_GA_Combo3::OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo3::OnNotifyEnd", 222);

	if (!CollisionBoxComponent)return;
	// �R���W�����𖳌��ɂ���
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!CollisionBoxComponent) return;

	if (NotifyName == "OnCollision")
	{
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//OnNotifyBegin���Ă΂ꂽ���ɂ�Notify�Ή�����^�O��ǉ����A
	//RemoveGameplayTags���Ă΂ꂽ���ɂ�Notify�ɑΉ�����^�O�������B
	//Combo1.Input �� Ability.Ready.Combo2
	//Combo1.Branch �� Ability.Begin.Combo2
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
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo1::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}
