// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SFA_InputHandlerComponent.generated.h"



UENUM(BlueprintType)
enum class ESFA_InputState : uint8
{
	None,

	Both_enable,
	Move_disable,
	//Action_disable,
	//Both_disable,

	ElementsNum,
};

UENUM(BlueprintType)
enum class ESFA_MoveState : uint8
{
	None,

	Glide,	// move in air
	Walk,	// move on land
	Dash,	// jump or dash in air

	Land,	// idle on land
	Jump,	// jump on land
	Float,	// idle in air

	Dive,	// 
	Fall,	// 

	ElementsNum,
};

UENUM(BlueprintType)
enum class ESFA_AttackState : uint8
{
	None,

	NormalAttack,	// normal 1
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	///////////////// custom property
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESFA_InputState InputState = ESFA_InputState::Both_enable;
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

	//TODO add playerAbilities

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DiveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ShortRangeAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LongRangeAttackAction;

private:
	//~Parameters for components
	ASFA_Camera* Camera;
	ASFA_Player* Player;
	USFA_PlayerStateMachine* PlayerStateMachine;
	USFA_PlayerMovementComponent* PlayerMovementComponent;
	//~End of Parameters for components


	///////////////// custom function
public:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void ShortRangeAttack();
	void LongRangeAttack();
	void InitializePointers();
};
