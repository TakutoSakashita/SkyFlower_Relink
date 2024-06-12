// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFA_IDamageable.h"
#include "SFA_EnemyBase.generated.h"

class UNiagaraComponent;
class USphereComponent;
class UArrowComponent;
class UStaticMeshComponent;
class ASFA_Player;
class UParticleSystem;
class USoundBase;

UCLASS()
class ASTERISK_API ASFA_EnemyBase : public APawn, public ISFA_IDamageable
{
	GENERATED_BODY()

public:
	ASFA_EnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//~BEGIN ISFA_IDamageable
public:
	virtual void TakeDamage(AActor* Aggressor, float Damage) override;

private:
	UFUNCTION()
	void Die();
	UPROPERTY()
	float Health = 100.f;
	//~END


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ASFA_Player* PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathEffect;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
};
