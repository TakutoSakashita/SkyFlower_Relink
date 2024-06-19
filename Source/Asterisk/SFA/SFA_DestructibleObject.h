// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFA_IDamageable.h"
#include "SFA_DestructibleObject.generated.h"

UCLASS()
class ASTERISK_API ASFA_DestructibleObject : public AActor , public ISFA_IDamageable
{
	GENERATED_BODY()
	
public:	
	ASFA_DestructibleObject();
	
protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	void DestroyObject();

public:
	virtual void TakeDamage(AActor* Aggressor, float Damage) override;

	UPROPERTY()
	float Health = 100.f;
};
