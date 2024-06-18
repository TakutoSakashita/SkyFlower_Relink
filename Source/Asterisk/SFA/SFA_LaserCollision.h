// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFA_LaserCollision.generated.h"

class USphereComponent;

UCLASS()
class ASTERISK_API ASFA_LaserCollision : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASFA_LaserCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	AActor* Aggressor = nullptr;
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UFUNCTION(BlueprintCallable)
	void Initialize(AActor* AggressorActor, FVector MoveDirection, float MoveSpeed, float LifeSpan = 3.f, float InitDamage = 10.f);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// UProjectileMovementComponent* ProjectileMovement;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;

	UFUNCTION()
	void Move();

	UPROPERTY()
	FVector Direction = FVector::ZeroVector;

	UPROPERTY()
	float Speed = 0.f;
};
