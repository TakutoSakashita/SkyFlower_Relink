// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SFA_PlayerMovementComponent.generated.h"

class ASFA_Player;
class UAnimInstance;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTERISK_API USFA_PlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	USFA_PlayerMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY()
	bool bForce = false;
	UPROPERTY()
	float forceValue = 300.f;
	UFUNCTION()
	void UpdateForce(float DeltaTime);
	UFUNCTION()
	void SweepMove(FVector MoveVector, float MoveSpeed);

private:
	UFUNCTION()
	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false, bool bDrawPersistentShapes = false);
	UFUNCTION()
	bool CheckHasReachedFloor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> > SurfaceTraceTypes;

	UPROPERTY()
	ASFA_Player* Player;
	UPROPERTY()
	UAnimInstance* AnimInstance;
};
