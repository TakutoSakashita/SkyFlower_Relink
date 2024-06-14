#pragma once

#include "CoreMinimal.h"
#include "SFA_BlogComboGameplayAbility.h"
#include "SFA_GA_Combo1.generated.h"

class ASFA_Player;

UCLASS()
class ASTERISK_API USFA_GA_Combo1 : public USFA_BlogComboGameplayAbility
{
	GENERATED_BODY()
	USFA_GA_Combo1();
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
	FGameplayTag AbilityBeginTagName;
	UPROPERTY(EditAnywhere, Category = "Tag")
	FGameplayTag AbilityReadyTagName;
	UPROPERTY(EditAnywhere, Category = "State")
	float DistanceThreshold = 1000.0f;
	UPROPERTY(EditAnywhere, Category = "State")
	float DesiredDistance = 100.0f; 
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;

	AActor* GetClosestActor(const FVector& SourceLocation, TArray<AActor*> PotentialTargets);
private:
	UFUNCTION()
	void OnBlendOut(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	UFUNCTION()
	void OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	UFUNCTION()
	void HandleMyTagAdded();
};
