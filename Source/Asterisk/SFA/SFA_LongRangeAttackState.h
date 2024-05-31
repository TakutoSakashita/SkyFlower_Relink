#pragma once

#include "CoreMinimal.h"
#include "SFA_PlayerStateBase.h"
#include "SFA_LongRangeAttackState.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class ASTERISK_API USFA_LongRangeAttackState : public USFA_PlayerStateBase
{
	GENERATED_BODY()

public:
	USFA_LongRangeAttackState();

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

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///////////////////////////// custom variable
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere, Category = "TEST")
	UParticleSystem* ParticleEffect;

private:

	int32 hitDamage;
};
