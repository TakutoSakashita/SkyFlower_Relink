
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
#include "../DebugHelpers.h"


#define MIN_VALID_MAGNITUDE 0.1f

USFA_InputHandlerComponent::USFA_InputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USFA_InputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializePointers();

	// load InputMappingContext
	ASFA_PlayerController* controller = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (controller)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void USFA_InputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(Camera) || !IsValid(Player)) InitializePointers(); // debug for packaging


}

void USFA_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &USFA_InputHandlerComponent::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &USFA_InputHandlerComponent::Look);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &USFA_InputHandlerComponent::Dash);
		EnhancedInputComponent->BindAction(DropAttackAction, ETriggerEvent::Started, this, &USFA_InputHandlerComponent::DropAttack);

		//TODO add playerAbilities
		EnhancedInputComponent->BindAction(ShortRangeAttackAction, ETriggerEvent::Started, this, &USFA_InputHandlerComponent::ShortRangeAttack);
		EnhancedInputComponent->BindAction(LongRangeAttackAction, ETriggerEvent::Started, this, &USFA_InputHandlerComponent::LongRangeAttack);
	}
}

void USFA_InputHandlerComponent::Look(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() < MIN_VALID_MAGNITUDE) return;
	if (!IsValid(Camera)) return;

	//todo move to StateMachine
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		Camera->Turn(LookAxisVector.X);
		Camera->LookUp(LookAxisVector.Y);
	}
}

void USFA_InputHandlerComponent::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() < MIN_VALID_MAGNITUDE) return;
	if (!IsValid(Camera) || !IsValid(Player)) return;
	if (InputState == ESFA_InputState::Move_disable) return;

	//PlayerStateMachine->SwitchStateByKey("Float");

	//todo move to StateMchine
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		Player->AddMovementInput(Camera->GetActorForwardVector(), MovementVector.Y);
		Player->AddMovementInput(Camera->GetActorRightVector(), MovementVector.X);
	}
}

void USFA_InputHandlerComponent::Dash(const FInputActionValue& Value)
{
	if (InputState == ESFA_InputState::Move_disable) return;
	PlayerStateMachine->SwitchStateByKey("Dash");
}

void USFA_InputHandlerComponent::DropAttack(const FInputActionValue& Value)
{
	if (InputState == ESFA_InputState::Move_disable) return;
	if (PlayerMovementComponent->MovementMode == EMovementMode::MOVE_Walking) return;
	PlayerStateMachine->SwitchStateByKey("DropAttack");
}

void USFA_InputHandlerComponent::ShortRangeAttack()
{
	PlayerStateMachine->SwitchStateByKey("ShortRangeAttack");
}

void USFA_InputHandlerComponent::LongRangeAttack()
{
	PlayerStateMachine->SwitchStateByKey("LongRangeAttack");
}

void USFA_InputHandlerComponent::InitializePointers()
{
	Camera = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	Player = Cast<ASFA_Player>(GetOwner());
	PlayerStateMachine = Player->GetPlayerStateMachine();
	PlayerMovementComponent = Player->GetPlayerMovement();
}
