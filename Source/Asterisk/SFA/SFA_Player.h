// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "SFA_Player.generated.h"

class USFA_InputHandlerComponent;
class USFA_PlayerMovementComponent;
class ASFA_Weapon;
class UAbilitySystemComponent;
class USFA_PlayerStateMachine;

UCLASS()
class ASTERISK_API ASFA_Player : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

		///////////////// override function
public:
	ASFA_Player(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom parameter
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USFA_InputHandlerComponent* InputHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USFA_PlayerMovementComponent* PlayerMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USFA_PlayerStateMachine* PlayerStateMachine;

protected:
	// AbilitySystemを使用するうえで必須のコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAbilitySystemComponent* AbilitySystem;

	// このキャラクターが持つアビリティの配列
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
		TArray<TSubclassOf<UGameplayAbility>> AbilityList;

public:
	FORCEINLINE USFA_InputHandlerComponent* GetInputHandler() const { return InputHandler; }
	FORCEINLINE USFA_PlayerMovementComponent* GetPlayerMovement() const { return PlayerMovement; }
	FORCEINLINE USFA_PlayerStateMachine* GetPlayerStateMachine() const { return PlayerStateMachine; }

	UPROPERTY(BlueprintReadWrite)
	ASFA_Weapon* Weapon = nullptr;
	UFUNCTION(BlueprintCallable)
	ASFA_Weapon* GetWeapon() const { return Weapon; };
	UFUNCTION(BlueprintImplementableEvent)
	void InitWeapon();

	// 新しいControllerが与えられたときにAbility Systemのアクタをリフレッシュする
	virtual void PossessedBy(AController* NewController) override;
	// Ability System Componentのゲッター
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystem; }



};
