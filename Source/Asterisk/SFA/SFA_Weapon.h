// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFA_Weapon.generated.h"

class UBoxComponent;
class USoundBase;

UCLASS()
class ASTERISK_API ASFA_Weapon : public AActor
{
	GENERATED_BODY()

public:
	ASFA_Weapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float hitDamage = 30;
	UPROPERTY ()
	AActor* Aggressor = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UBoxComponent* GetBoxComponent() { return BoxComponent; }

	UPROPERTY(EditAnywhere, Category = "TEST")
	UParticleSystem* ParticleEffect;
};
