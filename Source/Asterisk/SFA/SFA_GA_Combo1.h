// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFA_BlogComboGameplayAbility.h"
#include "SFA_GA_Combo1.generated.h"

class ASFA_Player;

UCLASS()
class ASTERISK_API USFA_GA_Combo1 : public USFA_BlogComboGameplayAbility
{
	GENERATED_BODY()

public:
	ASFA_Player* Player;

	// AnimInstance
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UAnimInstance* AnimInstance;
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "SwitchOnName")
	FName nInput;
	UPROPERTY(EditAnywhere, Category = "SwitchOnName")
	FName nBranch;
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)override;

private:
	void OnBlendOut(UAnimMontage* Montage, bool bInterrupted);
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	void OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
