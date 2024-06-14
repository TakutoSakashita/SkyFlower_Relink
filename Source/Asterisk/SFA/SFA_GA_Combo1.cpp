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

    if (!IsValid(Player)) {
        Debug::PrintFixedLine("USFA_GA_Combo1 : PlayerNull", 222);
        return;
    }

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) {
        Debug::PrintFixedLine("USFA_GA_Combo1 : CommitAbilityNull", 222);
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    AnimInstance = Player->GetMesh()->GetAnimInstance();
    if (!IsValid(AnimInstance)) {
        Debug::PrintFixedLine("USFA_GA_Combo1 : AnimInstanceNull", 222);
        return;
    }

    // // タグを削除
    // FGameplayTagContainer TagContainer;
    // TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo2"));
    // RemoveGameplayTags(TagContainer);
    //
    // TagContainer.Reset();  // 以前のタグをクリア
    // TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo2"));
    // RemoveGameplayTags(TagContainer);

    ASFA_Weapon* SFA_Weapon = Player->GetWeapon();
    if (!SFA_Weapon) {
        UE_LOG(LogTemp, Warning, TEXT("SFA_Weapon :null"));
        return;
    }

    CollisionBoxComponent = SFA_Weapon->GetBoxComponent();
    if (!CollisionBoxComponent) {
        UE_LOG(LogTemp, Warning, TEXT("CollisionBoxComponent :null"));
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

            // 敵から理想的な距離に位置するターゲットオフセットを計算
            FVector DirectionToTarget = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
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

            //ApplyRootMotionConstantForce->OnFinished.AddDynamic(this, &USFA_GA_Combo2::OnMoveCompleted);
            //OnTimedOut.AddDynamic(this, &USFA_GA_Combo2::OnMoveCompleted);
            //ApplyRootMotionConstantForce->OnTimedOutAndDestinationReached.AddDynamic(this, &USFA_GA_Combo2::OnMoveCompleted);

            ApplyRootMotionConstantForce->ReadyForActivation();
        }
    }

    UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
        this,
        FGameplayTag::RequestGameplayTag(FName("Ability.State.Combo1")),
        nullptr,
        false);

    if (Task)
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

    TagContainer.Reset();  // 以前のタグをクリア
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
    if (NotifyName == nInput) {
        TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
    } else if (NotifyName == nBranch) {
        TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
    } else {
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
    
    if (NotifyName == nInput) {
        TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
    } else if (NotifyName == nBranch) {
        TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
    } else {
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
