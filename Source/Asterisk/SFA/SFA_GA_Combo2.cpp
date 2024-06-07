#include "SFA_GA_Combo2.h"
#include "Kismet/GameplayStatics.h"

void USFA_GA_Combo2::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo2"));

	Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Player)) {
		Debug::PrintFixedLine("USFA_GA_Combo1 : PlayerNull", 222);
		return;
	};

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) {
		Debug::PrintFixedLine("USFA_GA_Combo1 : CommitAbilityNull", 222);
		return;
	}

	UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this, // アビリティの所有者
		FGameplayTag::RequestGameplayTag("Ability.Begin.Combo2"), // 監視するゲームプレイタグ
		Player,
		false // OptionalExternalTargetを使用しない場合はfalse
	);
	if (Task)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task"));
		HandleMyTagAdded();
		// タグが追加されたときの処理を設定
		Task->Added.AddDynamic(this, &USFA_GA_Combo2::HandleMyTagAdded);
	}
}

void USFA_GA_Combo2::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
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
		Debug::PrintFixedLine("USFA_GA_Combo1 : AnimInstanceNull", 222);
		return;
	};

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
	if (bInterrupted) {
		// 中断された場合の処理
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
		UE_LOG(LogTemp, Warning, TEXT("OnInterrupted"));
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
}

void USFA_GA_Combo2::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyBegin", 222);

	//OnNotifyBeginが呼ばれた時にはNotify対応するタグを追加し、
	//RemoveGameplayTagsが呼ばれた時にはNotifyに対応するタグを消す。
	//Combo1.Input → Ability.Ready.Combo2
	//Combo1.Branch → Ability.Begin.Combo2
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

void USFA_GA_Combo2::OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyEnd", 222);

	//OnNotifyBeginが呼ばれた時にはNotify対応するタグを追加し、
	//RemoveGameplayTagsが呼ばれた時にはNotifyに対応するタグを消す。
	//Combo1.Input → Ability.Ready.Combo2
	//Combo1.Branch → Ability.Begin.Combo2
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
