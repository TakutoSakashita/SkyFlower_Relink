
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

// AattackInput
//#include "A_Weapon.h"
#include "Components/BoxComponent.h" 

//debug
#include "../DebugHelpers.h"


#define MIN_VALID_MAGNITUDE 0.09f

USFA_InputHandlerComponent::USFA_InputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

//////////////////////////////////// NotifyEvent
void USFA_InputHandlerComponent::StartCollision()
{
	// コリジョン有効
	Debug::PrintFixedLine("StartCollision");
}

void USFA_InputHandlerComponent::EndCollision()
{
	// コリジョン無効
	Debug::PrintFixedLine("EndCollision");
}

void USFA_InputHandlerComponent::StartCombo()
{
	// コンボ入力受付開始
	ComboAccept = true;
}

void USFA_InputHandlerComponent::EndCombo()
{
	// コンボ入力受付終了
	ComboAccept = false;
}
void USFA_InputHandlerComponent::ResetCombo()
{
	// コンボリセット
	ComboAccept = true;
	ComboCount = 0;
}
//////////////////////////////////// NotifyEvent

void USFA_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &USFA_InputHandlerComponent::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &USFA_InputHandlerComponent::Look);

		//TODO add playerAbilities
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &USFA_InputHandlerComponent::Attack);


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

void USFA_InputHandlerComponent::Attack()
{
	if (!ComboAccept)return;
	ComboCount++;
	ComboAccept = false;

	//GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

	// ComboMontageはAnimMontageへのポインタを保持している変数
	AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (AttackMontage && AnimInstance)
	{
		Debug::PrintFixedLine("AttackMontage");

		//UE_LOG(LogTemp, Warning, TEXT("ComboMontage"));

		FString SectionName = FString::Printf(TEXT("Attack0%d"), ComboCount);
		FName SectionFName(*SectionName);

		Player->PlayAnimMontage(AttackMontage, 1.0f, SectionFName);
	}
}

void USFA_InputHandlerComponent::InitializePointers()
{
	Camera = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	Player = Cast<ASFA_Player>(GetOwner());
	PlayerStateMachine = Player->GetPlayerStateMachine();
	PlayerMovementComponent = Player->GetPlayerMovement();
}
