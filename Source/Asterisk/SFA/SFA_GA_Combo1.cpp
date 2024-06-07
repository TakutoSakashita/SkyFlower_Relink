#include "SFA_GA_Combo1.h"

void USFA_GA_Combo1::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Player = Cast<ASFA_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Player)) {
		Debug::PrintFixedLine("USFA_GA_Combo1 : PlayerNull", 222);
		return;
	};

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) {
		Debug::PrintFixedLine("USFA_GA_Combo1 : CommitAbilityNull", 222);
		return;
	}

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) {
		Debug::PrintFixedLine("USFA_GA_Combo1 : AnimInstanceNull", 222);
		return;
	};

	// �A�j���[�V�����Đ�
	AnimInstance->Montage_Play(AttackMontage);

	// �A�j���[�V�����֘A�̒ʒm
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo1::OnBlendOut);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo1::OnNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo1::OnNotifyEnd);
}

void USFA_GA_Combo1::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle,ActorInfo,ActivationInfo, bReplicateEndAbility,bWasCancelled);
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo2"));
	RemoveGameplayTags(TagContainer);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo2"));
	RemoveGameplayTags(TagContainer);
}

void USFA_GA_Combo1::OnBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBlendOut"));
	if (bInterrupted) {
		// ���f���ꂽ�ꍇ�̏���
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
		UE_LOG(LogTemp, Warning, TEXT("OnInterrupted"));
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
}

void USFA_GA_Combo1::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyBegin", 222);

	//OnNotifyBegin���Ă΂ꂽ���ɂ�Notify�Ή�����^�O��ǉ����A
	//RemoveGameplayTags���Ă΂ꂽ���ɂ�Notify�ɑΉ�����^�O�������B
	//Combo1.Input �� Ability.Ready.Combo2
	//Combo1.Branch �� Ability.Begin.Combo2
	if (NotifyName == nInput)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo2"));
		AddGameplayTags(TagContainer);
	}
	else if (NotifyName == nBranch)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo2"));
		AddGameplayTags(TagContainer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo1::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}

void USFA_GA_Combo1::OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyEnd", 222);

	//OnNotifyBegin���Ă΂ꂽ���ɂ�Notify�Ή�����^�O��ǉ����A
	//RemoveGameplayTags���Ă΂ꂽ���ɂ�Notify�ɑΉ�����^�O�������B
	//Combo1.Input �� Ability.Ready.Combo2
	//Combo1.Branch �� Ability.Begin.Combo2
	if (NotifyName == nInput)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo2"));
		RemoveGameplayTags(TagContainer);
	}
	else if (NotifyName == nBranch)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo2"));
		RemoveGameplayTags(TagContainer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USFA_GA_Combo1::Name not found ,NotifyName : %s"), *NotifyName.ToString());
	}
}