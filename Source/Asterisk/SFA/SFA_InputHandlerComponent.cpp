#include "SFA_InputHandlerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SFA_PlayerController.h"
// player components
#include "SFA_Camera.h"
#include "SFA_Player.h"
#include "SFA_PlayerMovementComponent.h"
#include "SFA_PlayerStateMachine.h"
// enhanced input
#include "Components/InputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"

//debug
#include "SFA_HUD.h"
#include "../DebugHelpers.h"
#include "GameFramework/GameModeBase.h"


USFA_InputHandlerComponent::USFA_InputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USFA_InputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializePointers();

	// load InputMappingContext
	ASFA_PlayerController* controller = Cast<ASFA_PlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (controller)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void USFA_InputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CameraRef) || !IsValid(PlayerRef)) InitializePointers(); // debug for packaging
}

void USFA_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &USFA_InputHandlerComponent::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		                                   &USFA_InputHandlerComponent::Look);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::Dash);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::Jump);
		EnhancedInputComponent->BindAction(DropAttackAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::DropAttack);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::StartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this,
		                                   &USFA_InputHandlerComponent::EndAim);

		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::StartBoost);
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Triggered, this,
		                                   &USFA_InputHandlerComponent::UpdateBoost);
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Completed, this,
		                                   &USFA_InputHandlerComponent::EndBoost);


		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::Shoot);
		//TODO add playerAbilities
		EnhancedInputComponent->BindAction(ShortRangeAttackAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::ShortRangeAttack);
		EnhancedInputComponent->BindAction(LongRangeAttackAction, ETriggerEvent::Started, this,
		                                   &USFA_InputHandlerComponent::LongRangeAttack);
	}
}

void USFA_InputHandlerComponent::Look(const FInputActionValue& Value)
{
	PlayerStateMachineRef->Look(Value);
}

void USFA_InputHandlerComponent::Move(const FInputActionValue& Value)
{
	if (!bCanMove) return;

	PlayerStateMachineRef->Move(Value);
}

void USFA_InputHandlerComponent::Dash(const FInputActionValue& Value)
{
	if (!bCanMove) return;
	PlayerStateMachineRef->SwitchStateByKey("Dash");
}

void USFA_InputHandlerComponent::Jump(const FInputActionValue& Value)
{
	if (!bCanMove) return;
	PlayerStateMachineRef->SwitchStateByKey("Jump");
}

void USFA_InputHandlerComponent::DropAttack(const FInputActionValue& Value)
{
	if (!bCanMove) return;
	if (PlayerMovementComponentRef->MovementMode == EMovementMode::MOVE_Walking) return;
	PlayerStateMachineRef->SwitchStateByKey("DropAttack");
}

void USFA_InputHandlerComponent::StartAim(const FInputActionValue& Value)
{
	//TODO null check
	//TODO revise player rotation
	HudRef->ShowCrosshair(true);
	CameraRef->StartAim();
	PlayerStateMachineRef->bIsAiming = true;
	PlayerMovementComponentRef->bOrientRotationToMovement = false;
	PlayerMovementComponentRef->MaxFlySpeed = 900.f;
}

void USFA_InputHandlerComponent::EndAim(const FInputActionValue& Value)
{
	//TODO null check
	HudRef->ShowCrosshair(false);
	CameraRef->EndAim();
	PlayerStateMachineRef->bIsAiming = false;
	PlayerMovementComponentRef->bOrientRotationToMovement = true;
	PlayerMovementComponentRef->MaxFlySpeed = 1800.f;
}

void USFA_InputHandlerComponent::StartBoost(const FInputActionValue& Value)
{
	if (!IsValid(CameraRef)) return;
	CameraRef->StartBoost();
	PlayerStateMachineRef->bIsBoosting = true;
	PlayerMovementComponentRef->MaxFlySpeed = 8000.f;
}

void USFA_InputHandlerComponent::UpdateBoost(const FInputActionValue& Value)
{
	if (!IsValid(PlayerRef)) return;

	//auto moving forward
	PlayerRef->AddMovementInput(CameraRef->GetActorForwardVector(), 1.f);
}

void USFA_InputHandlerComponent::EndBoost(const FInputActionValue& Value)
{
	if (!IsValid(CameraRef)) return;
	CameraRef->EndBoost();
	PlayerStateMachineRef->bIsBoosting = false;
	PlayerMovementComponentRef->MaxFlySpeed = 1800.f;
}

void USFA_InputHandlerComponent::Shoot(const FInputActionValue& Value)
{
	if (!bCanAttack) return;
	//TODO null check, state check
	PlayerStateMachineRef->SwitchStateByKey("Shoot");
}

void USFA_InputHandlerComponent::ShortRangeAttack()
{
	//PlayerStateMachine->SwitchStateByKey("ShortRangeAttack");
}

void USFA_InputHandlerComponent::LongRangeAttack()
{
	//PlayerStateMachine->SwitchStateByKey("LongRangeAttack");
}

void USFA_InputHandlerComponent::InitializePointers()
{
	CameraRef = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	PlayerRef = Cast<ASFA_Player>(GetOwner());
	PlayerStateMachineRef = PlayerRef->GetPlayerStateMachine();
	PlayerMovementComponentRef = PlayerRef->GetPlayerMovement();

	HudRef = Cast<ASFA_HUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
}
