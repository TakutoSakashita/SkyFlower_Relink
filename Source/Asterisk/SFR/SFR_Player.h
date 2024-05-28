// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SFR_Player.generated.h"


class UCapsuleComponent;
class USkeletalMeshComponent;
class USFR_InputHandlerComponent;
class USFR_PlayerStateMachine;


UCLASS()
class ASTERISK_API ASFR_Player : public APawn
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
	USFR_PlayerStateMachine* PlayerStateMachine;
	USFR_PlayerStateMachine* GetPlayerStateMachine() const { return PlayerStateMachine; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* CapsuleComponent;
	UCapsuleComponent* GetCapsule()const { return CapsuleComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
	USkeletalMeshComponent* GetMesh()const { return SkeletalMeshComponent; }

};
