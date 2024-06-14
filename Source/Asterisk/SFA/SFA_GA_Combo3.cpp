// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_GA_Combo3.h"

void USFA_GA_Combo3::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UAbilityTask_WaitGameplayTagAdded* Task = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this, 
		FGameplayTag::RequestGameplayTag(FName("Ability.Begin.Combo3")),
		nullptr, 
		false);
	//Task->Activate();

	if (Task)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task"));
		//HandleMyTagAdded();
		// �^�O���ǉ����ꂽ�Ƃ��̏�����ݒ�
		Task->Added.AddDynamic(this, &USFA_GA_Combo3::HandleMyTagAdded);
		Task->ReadyForActivation();

	}
}

void USFA_GA_Combo3::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo4"));
	RemoveGameplayTags(TagContainer);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Begin.Combo4"));
	RemoveGameplayTags(TagContainer);
}

void USFA_GA_Combo3::HandleMyTagAdded()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleMyTagAdded"));

	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance)) {
		Debug::PrintFixedLine("USFA_GA_Combo1 : AnimInstanceNull", 222);
		return;
	};

	// �A�j���[�V�����Đ�
	AnimInstance->Montage_Play(AttackMontage);

	// �A�j���[�V�����֘A�̒ʒm
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo3::OnBlendOut);
	//AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo3::OnNotifyBegin);
	//AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo3::OnNotifyEnd);
}

void USFA_GA_Combo3::OnBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBlendOut"));
	if (bInterrupted) {
		// ���f���ꂽ�ꍇ�̏���
		//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
		UE_LOG(LogTemp, Warning, TEXT("OnInterrupted"));
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
}

void USFA_GA_Combo3::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyBegin", 222);

	ASFA_Weapon* SFA_Weapon = Player->GetWeapon();
	if (!SFA_Weapon) return;

	CollisionBoxComponent = SFA_Weapon->GetBoxComponent();

	if (!CollisionBoxComponent)return;
	// �R���W������L���ɂ���
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

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
	Debug::PrintFixedLine("USFA_GA_Combo1::OnNotifyEnd", 222);

	if (!CollisionBoxComponent)return;
	// �R���W�����𖳌��ɂ���
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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