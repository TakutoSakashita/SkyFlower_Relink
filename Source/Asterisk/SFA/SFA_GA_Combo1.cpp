#include "SFA_GA_Combo1.h"

USFA_GA_Combo1::USFA_GA_Combo1()
{
	// �^�O�̏�����
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
	// ���ׂĂ̓G�L�����N�^�[���擾����
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFA_EnemyBase::StaticClass(), PotentialTargets);

	if (AActor* ClosestTarget = GetClosestActor(SourceLocation, PotentialTargets))
	{
		float DistanceToTarget = FVector::Dist(SourceLocation, ClosestTarget->GetActorLocation());
		if (DistanceToTarget < DistanceThreshold)
		{
			// �G�̕���������
			FRotator TargetRotation = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).Rotation();
			Player->SetActorRotation(TargetRotation);

			// �G���痝�z�I�ȋ����Ɉʒu����^�[�Q�b�g�I�t�Z�b�g���v�Z
			FVector DirectionToTarget = (ClosestTarget->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
			FVector TargetLocationOffset = DirectionToTarget * DesiredDistance;

			UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionConstantForce =
				UAbilityTask_ApplyRootMotionMoveToActorForce::ApplyRootMotionMoveToActorForce(
					this,
					FName("MoveToTarget"), // �^�X�N�̖��O��"MoveToTarget"�ɐݒ�
					ClosestTarget, // �ł��߂��^�[�Q�b�g
					TargetLocationOffset, // �^�[�Q�b�g�̈ʒu�I�t�Z�b�g
					ERootMotionMoveToActorTargetOffsetType::AlignFromTargetToSource, // �^�[�Q�b�g����\�[�X�ւ̃I�t�Z�b�g�^�C�v��ݒ�
					MoveToTargetDuration, // �^�[�Q�b�g�ւ̈ړ�����
					nullptr, // ���������̃^�[�Q�b�g�̕�ԑ��x
					nullptr, // ���������̃^�[�Q�b�g�̕�ԑ��x
					true, // �V�����ړ����[�h��ݒ肷��
					EMovementMode::MOVE_Walking, // �ړ����[�h����s�ɐݒ�
					true, // ���҂���鑬�x�ɐ�������
					nullptr, // �p�X�I�t�Z�b�g�J�[�u
					nullptr, // �^�C���}�b�s���O�J�[�u
					ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity, // �Ō�̃��[�g���[�V�����̑��x���ێ�
					FVector::ZeroVector, // �I�����̑��x���[���x�N�g���ɐݒ�
					0.f, // �I�����̑��x�𐧌�����
					false // �ړI�n���B�̊��荞�݂𖳌��ɂ��Ȃ�
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

	// �^�O���폜
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Ready.Combo2"));
	RemoveGameplayTags(TagContainer);

	TagContainer.Reset(); // �ȑO�̃^�O���N���A
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
		// �R���W�����𖳌��ɂ���
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		// �R���W�����𖳌��ɂ���
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
		// �R���W������L���ɂ���
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	// �^�O�̒ǉ�
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
		// �R���W�����𖳌��ɂ���
		CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// �^�O�̍폜
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
	// �A�j���[�V�����Đ�
	AnimInstance->Montage_Play(AttackMontage);

	// �A�j���[�V�����֘A�̒ʒm
	AnimInstance->OnMontageBlendingOut.AddDynamic(this, &USFA_GA_Combo1::OnBlendOut);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &USFA_GA_Combo1::OnNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &USFA_GA_Combo1::OnNotifyEnd);
}
