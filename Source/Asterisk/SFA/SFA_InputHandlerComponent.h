// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SFA_InputHandlerComponent.generated.h"


class ASFA_HUD;

UENUM(BlueprintType)
enum class ESFA_InputState : uint8
{
	None,

	Both_enable,
	Move_disable,
	//Action_disable,
	Both_disable,

	ElementsNum,
};

UENUM(BlueprintType)
enum class ESFA_MoveState : uint8
{
	None,

	Glide, // move in air
	Walk, // move on land
	Dash, // jump or dash in air

	Land, // idle on land
	Jump, // jump on land
	Float, // idle in air

	Dive, // 
	Fall, // 

	ElementsNum,
};

UENUM(BlueprintType)
enum class ESFA_AttackState : uint8
{
	None,

	NormalAttack, // normal 1
	HomingAttack,
	LaserAttack,

	ElementsNum,
};


struct FInputActionValue;
class UInputComponent;
class UInputMappingContext;
class UInputAction;

class ASFA_Camera;
class ASFA_Player;
class USFA_PlayerStateMachine;
class USFA_PlayerMovementComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTERISK_API USFA_InputHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

	///////////////// override function
public:
	USFA_InputHandlerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom property
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanMove = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanAttack = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESFA_MoveState MoveState = ESFA_MoveState::Float;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESFA_AttackState AttackState = ESFA_AttackState::None;


	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	/** Action Input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DropAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AimAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* BoostAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	//TODO add playerAbilities

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DiveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ShortRangeAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LongRangeAttackAction;

private:
	//~BEGIN Parameters for components
	UPROPERTY()
	ASFA_Camera* CameraRef;
	UPROPERTY()
	ASFA_Player* PlayerRef;
	UPROPERTY()
	USFA_PlayerStateMachine* PlayerStateMachineRef;
	UPROPERTY()
	USFA_PlayerMovementComponent* PlayerMovementComponentRef;
	UPROPERTY()
	ASFA_HUD* HudRef;
	//~END of Parameters for components


	///////////////// custom function
public:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void DropAttack(const FInputActionValue& Value);
	void StartAim(const FInputActionValue& Value);
	void EndAim(const FInputActionValue& Value);
	void StartBoost(const FInputActionValue& Value);
	void UpdateBoost(const FInputActionValue& Value);
	void EndBoost(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void ShortRangeAttack();
	void LongRangeAttack();
	void InitializePointers();
};
