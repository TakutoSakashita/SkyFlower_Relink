// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SFA_Player.generated.h"



class USFA_InputHandlerComponent;
class USFA_PlayerMovementComponent;
class USFA_PlayerStateMachine;



UCLASS()
class ASTERISK_API ASFA_Player : public ACharacter
{
	GENERATED_BODY()

	///////////////// override function
public:
	ASFA_Player(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom parameter
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USFA_InputHandlerComponent* InputHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USFA_PlayerMovementComponent* PlayerMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USFA_PlayerStateMachine* PlayerStateMachine;


public:
	FORCEINLINE USFA_InputHandlerComponent* GetInputHandler() const { return InputHandler; }
	FORCEINLINE USFA_PlayerMovementComponent* GetPlayerMovement() const { return PlayerMovement; }
	FORCEINLINE USFA_PlayerStateMachine* GetPlayerStateMachine() const { return PlayerStateMachine; }



};
