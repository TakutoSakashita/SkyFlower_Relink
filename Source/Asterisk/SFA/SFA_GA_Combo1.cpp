#include "SFA_GA_Combo1.h"

USFA_GA_Combo1::USFA_GA_Combo1()
{
	// タグの初期化
	this->ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.State.Combo1")));
	this->ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.State")));
	this->AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Action.Attack")));
}

void USFA_GA_Combo1::ActivateAbility(
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

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) return;

	ASFA_Weapon* SFA_Weapon = Player->GetWeapon();
	if (!SFA_Weapon) return;

	CollisionBoxComponent = SFA_Weapon->GetBoxComponent();
	if (!CollisionBoxComponent) return;

	FVector SourceLocation = Player->GetActorLocation();
	TArray<AActor*> PotentialTargets;
	// すべての敵キャラクターを取得する
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
			FVector DirectionToTarget = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
			FVector TargetLocationOffset = DirectionToTarget * DesiredDistance;

			UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionConstantForce =
				UAbilityTask_ApplyRootMotionMoveToActorForce::ApplyRootMotionMoveToActorForce(
					this,
					FName("MoveToTarget"), // タスクの名前を"MoveToTarget"に設定
					ClosestTarget, // 最も近いターゲット
					TargetLocationOffset, // ターゲットの位置オフセット
					ERootMotionMoveToActorTargetOffsetType::AlignFromTargetToSource, // ターゲットからソースへのオフセットタイプを設定
					MoveToTargetDuration, // ターゲットへの移動時間
					nullptr, // 水平方向のターゲットの補間速度
					nullptr, // 垂直方向のターゲットの補間速度
					true, // 新しい移動モードを設定する
					EMovementMode::MOVE_Walking, // 移動モードを歩行に設定
					true, // 期待される速度に制限する
					nullptr, // パスオフセットカーブ
					nullptr, // タイムマッピングカーブ
					ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity, // 最後のルートモーションの速度を維持
					FVector::ZeroVector, // 終了時の速度をゼロベクトルに設定
					0.f, // 終了時の速度を制限する
					false // 目的地到達の割り込みを無効にしない
				);
			ApplyRootMotionConstantForce->ReadyForActivation();
		}
	}

	if (UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this,
		FGameplayTag::RequestGameplayTag(FName("Ability.State.Combo1")),
		nullptr,
		false))
	{
		Task->Added.AddDynamic(this, &USFA_GA_Combo1::HandleMyTagAdded);
		Task->ReadyForActivation();
	}
}

void USFA_GA_Combo1::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// タグを削除
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo2"));
	RemoveGameplayTags(TagContainer);

	TagContainer.Reset(); // 以前のタグをクリア
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo2"));
	RemoveGameplayTags(TagContainer);
}

AActor* USFA_GA_Combo1::GetClosestActor(const FVector& SourceLocation, TArray<AActor*> PotentialTargets)
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

void USFA_GA_Combo1::OnBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBlendOut"));

	if (bInterrupted)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
}

void USFA_GA_Combo1::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyBegin", 222);

	if (!CollisionBoxComponent) return;

	if (NotifyName == "OnCollision")
	{
		// コリジョンを有効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	// タグの追加
	FGameplayTagContainer TagContainer;
	if (NotifyName == nInput)
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
	}
	else if (NotifyName == nBranch)
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo1::Name not found ,NotifyName : %s"), *NotifyName.ToString());
		return;
	}
	AddGameplayTags(TagContainer);
}

void USFA_GA_Combo1::OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyEnd", 222);

	if (!CollisionBoxComponent) return;

	if (NotifyName == "OnCollision")
	{
		// コリジョンを無効にする
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// タグの削除
	FGameplayTagContainer TagContainer;

	if (NotifyName == nInput)
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
	}
	else if (NotifyName == nBranch)
	{
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo1::Name not found ,NotifyName : %s"), *NotifyName.ToString());
		return;
	}
	RemoveGameplayTags(TagContainer);
}

void USFA_GA_Combo1::HandleMyTagAdded()
{
	// アニメーション再生
	AnimInstance->Montage_Play(AttackMontage);

	// アニメーション関連の通知
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo1::OnBlendOut);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo1::OnNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo1::OnNotifyEnd);
}
