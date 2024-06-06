#include "SFA_BlogComboGameplayAbility.h"

void USFA_BlogComboGameplayAbility::AddGameplayTags(const FGameplayTagContainer GameplayTags)
{
	UAbilitySystemComponent* Comp = GetAbilitySystemComponentFromActorInfo();

	/*Comp - &gt; */Comp->AddLooseGameplayTags(GameplayTags);
}

void USFA_BlogComboGameplayAbility::RemoveGameplayTags(const FGameplayTagContainer GameplayTags)
{
	UAbilitySystemComponent* Comp = GetAbilitySystemComponentFromActorInfo();

	/*Comp -> &gt; */Comp->RemoveLooseGameplayTags(GameplayTags);
	
}
