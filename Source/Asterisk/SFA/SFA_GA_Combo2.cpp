#include "SFA_GA_Combo2.h"

void USFA_GA_Combo2::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Player)) {
		Debug::PrintFixedLine("USFA_GA_Combo2 : PlayerNull", 222);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) {
		Debug::PrintFixedLine("USFA_GA_Combo2 : CommitAbilityNull", 222);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this,
		FGameplayTag::RequestGameplayTag(FName("Ability.Begin.Combo2")),
		nullptr,
		false);

	if (Task) {
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

void USFA_GA_Combo2::HandleMyTagAdded()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleMyTagAdded"));

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) {
		Debug::PrintFixedLine("USFA_GA_Combo2 : AnimInstanceNull", 222);
		return;
	}

	// アニメーション再生
	AnimInstance->Montage_Play(AttackMontage);

	// アニメーション関連の通知
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo2::OnBlendOut);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo2::OnNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo2::OnNotifyEnd);
}

void USFA_GA_Combo2::OnBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBlendOut"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
	if (bInterrupted) {
		UE_LOG(LogTemp, Warning, TEXT("OnInterrupted"));
	}
}

void USFA_GA_Combo2::OnNotifyBegin(FName NotifyName,
	const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo2::OnNotifyBegin", 222);

	ASFA_Weapon* SFA_Weapon = Player->GetWeapon();
	if (!SFA_Weapon) return;

	CollisionBoxComponent = SFA_Weapon->GetBoxComponent();

	if (!CollisionBoxComponent) return;
	// コリジョンを有効にする
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// NotifyNameに応じたタグの追加
	if (NotifyName == nInput) {
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
		AddGameplayTags(TagContainer);
	}
	else if (NotifyName == nBranch) {
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
		AddGameplayTags(TagContainer);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo2::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}

void USFA_GA_Combo2::OnNotifyEnd(FName NotifyName, 
	const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo2::OnNotifyEnd", 222);

	if (!CollisionBoxComponent) return;
	// コリジョンを無効にする
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// NotifyNameに応じたタグの削除
	if (NotifyName == nInput) {
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityReadyTagName.GetTagName()));
		RemoveGameplayTags(TagContainer);
	}
	else if (NotifyName == nBranch) {
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(AbilityBeginTagName.GetTagName()));
		RemoveGameplayTags(TagContainer);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo2::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}