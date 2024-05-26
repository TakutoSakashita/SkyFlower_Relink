// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFR_Player.generated.h"

class USFR_InputHandlerComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class USFR_MoveComponent;
class USFR_ActionComponent;

UCLASS()
class SKYFLOWER_API ASFR_Player : public APawn
{
	GENERATED_BODY()

	///////////////// override function
public:
	ASFR_Player();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	
	///////////////// custom parameter
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USFR_InputHandlerComponent* InputHandler;
	USFR_InputHandlerComponent* GetInputHandler() const { return InputHandler; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USFR_MoveComponent* MoveComponent;
	USFR_MoveComponent* GetMoveComponent() const { return MoveComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USFR_ActionComponent* ActionComponent;
	USFR_ActionComponent* GetActionComponent() const { return ActionComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* CapsuleComponent;
	UCapsuleComponent* GetCapsule()const { return CapsuleComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
	USkeletalMeshComponent* GetMesh()const { return SkeletalMeshComponent; }
};
