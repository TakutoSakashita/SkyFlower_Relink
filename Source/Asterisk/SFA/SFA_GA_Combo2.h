#pragma once

#include "CoreMinimal.h"
#include "SFA_BlogComboGameplayAbility.h"
#include "SFA_GA_Combo2.generated.h"

class ASFA_Player;

UCLASS()
class ASTERISK_API USFA_GA_Combo2 : public USFA_BlogComboGameplayAbility
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

	UPROPERTY(EditAnywhere, Category = "Tag")
	FGameplayTag  AbilityBeginTagName;
	UPROPERTY(EditAnywhere, Category = "Tag")
	FGameplayTag  AbilityReadyTagName;
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;
public:
	UFUNCTION()
	void HandleMyTagAdded();
	UFUNCTION()
	void OnBlendOut(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	UFUNCTION()
	void OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
