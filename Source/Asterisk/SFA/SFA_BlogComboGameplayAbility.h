#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../DebugHelpers.h"
#include "SFA_Player.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayTagContainer.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "SFA_BlogComboGameplayAbility.generated.h"

UCLASS()
class ASTERISK_API USFA_BlogComboGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	/** AbilitySystemComponent‚ÌGameplayTagCountContainer‚ÉV‚µ‚¢GameplayTag‚ğ’Ç‰Á‚·‚é */
	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	virtual void AddGameplayTags(const FGameplayTagContainer GameplayTags);

	/** AbilitySystemComponent‚ÌGameplayTagCountContainer‚ÌGameplayTag‚ğíœ‚·‚é */
	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	virtual void RemoveGameplayTags(const FGameplayTagContainer GameplayTags);
};
