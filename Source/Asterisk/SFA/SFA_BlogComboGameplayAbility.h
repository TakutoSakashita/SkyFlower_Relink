#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../DebugHelpers.h"
#include "SFA_Player.h"
#include "SFA_Weapon.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionMoveToActorForce.h"
#include "GameplayTagContainer.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "SFA_BlogComboGameplayAbility.generated.h"

class UBoxComponent;

UCLASS()
class ASTERISK_API USFA_BlogComboGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	/** AbilitySystemComponentのGameplayTagCountContainerに新しいGameplayTagを追加する */
	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	virtual void AddGameplayTags(const FGameplayTagContainer GameplayTags);

	/** AbilitySystemComponentのGameplayTagCountContainerのGameplayTagを削除する */
	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	virtual void RemoveGameplayTags(const FGameplayTagContainer GameplayTags);

protected:
	// Movement parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float MoveToTargetStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float MoveToTargetDuration;

public:
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBoxComponent;
};
