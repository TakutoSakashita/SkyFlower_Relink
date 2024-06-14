// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFA_Bullet.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class USoundBase;

UCLASS()
class ASTERISK_API ASFA_Bullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASFA_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void Initialize(const FVector& Vector, AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void SetBulletSpeed(const float Speed = 5000.f) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Aggressor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 20.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
	
};
