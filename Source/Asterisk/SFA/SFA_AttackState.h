#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_AttackState.generated.h"


UCLASS()
class ASTERISK_API USFA_AttackState : public USFA_PlayerStateBase
{
	GENERATED_BODY()
	
public:
	USFA_AttackState();

public:
	virtual void OnEnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;

public:
	/** Attack Input */

	// ƒRƒ“ƒ{“ü—ÍŽó•t true : start , false : end
	UPROPERTY(BlueprintReadOnly)
	bool ComboAccept = true;
	//UPROPERTY(BlueprintReadOnly)
	//	bool CanselAttack = true;
	UPROPERTY(BlueprintReadOnly)
	int ComboCount = 0;

	// AnimInstance
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AttackMontage;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UAnimInstance* AnimInstance;

	// function
	UFUNCTION(BlueprintCallable, Category = "Function")
	void StartCollision();
	UFUNCTION(BlueprintCallable, Category = "Function")
	void EndCollision();
	UFUNCTION(BlueprintCallable, Category = "Function")
	void StartCombo();
	UFUNCTION(BlueprintCallable, Category = "Function")
	void EndCombo();
	UFUNCTION(BlueprintCallable, Category = "Function")
	void ResetCombo();


};
