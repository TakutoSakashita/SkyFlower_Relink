// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFA_Fireball.generated.h"

UCLASS()
class ASTERISK_API ASFA_Fireball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASFA_Fireball();
	
protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shooting")
	TSubclassOf<class AActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shooting")
	int32 MaxProjectiles = 30;  // 発射する弾の最大数

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shooting")
	float ShootingAngleIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shooting")
	float ShootingRadius;

	UFUNCTION(BlueprintCallable, Category="Shooting")
	void ShootAllDirections();
};
