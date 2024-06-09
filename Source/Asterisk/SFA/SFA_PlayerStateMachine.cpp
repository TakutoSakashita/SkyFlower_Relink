// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_PlayerStateMachine.h"
#include "Kismet/GameplayStatics.h"
#include "SFA_PlayerController.h"
// player components
#include "SFA_Camera.h"
#include "SFA_Player.h"
#include "SFA_PlayerMovementComponent.h"
#include "SFA_InputHandlerComponent.h"
#include "SFA_PlayerStateBase.h"
// enhanced input
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
//debug
#include "../DebugHelpers.h"
#define LOG_PRINT 1
#define DEBUG_PRINT(text) if(LOG_PRINT) Debug::Print(text);
#define DEBUG_FIXED(text,num) if(LOG_PRINT) Debug::PrintFixedLine(text, num);
//bullet
#include "SFA_Bullet.h"

USFA_PlayerStateMachine::USFA_PlayerStateMachine()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USFA_PlayerStateMachine::BeginPlay()
{
	Super::BeginPlay();
	InitializePointers();
}

void USFA_PlayerStateMachine::InitializeStates()
{
	Super::InitializeStates();
	/*Create State and hold them in memory for when needed*/
	for (auto It = StateMap.CreateConstIterator(); It; ++It)
	{
		USFA_PlayerStateBase* state = Cast<USFA_PlayerStateBase>(It->Value);
		if (IsValid(state))
		{
			state->PlayerStateMachine = this;
			state->Camera = Camera;
			state->Player = Player;
			state->InputHandler = InputHandler;
			state->PlayerMovementComponent = PlayerMovementComponent;
		}
		DEBUG_PRINT(state->GetName())
	}
}

void USFA_PlayerStateMachine::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	Player->AddMovementInput(Camera->GetActorForwardVector(), MovementVector.Y);
	Player->AddMovementInput(Camera->GetActorRightVector(), MovementVector.X);
}

void USFA_PlayerStateMachine::Shoot(const FInputActionValue& Value)
{
	//TODO move to ShootState, setup moveSpeed and PlayerRotation
	FVector CameraPos = Camera->GetActorLocation();
	FRotator CameraRot = Camera->GetActorRotation();
	FVector CameraDir = CameraRot.Vector();
	FVector LineTraceEndDir = CameraPos + CameraDir * 50000.0f /* lineTrace length */;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Camera);
	CollisionParams.AddIgnoredActor(Player);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraPos, LineTraceEndDir, ECC_Visibility,
	                                                 CollisionParams);
	FVector BulletDestination;
	if (bHit) BulletDestination = HitResult.Location;
	else BulletDestination = LineTraceEndDir;

	FVector PlayerRightHandDir = Player->GetMesh()->GetSocketLocation(TEXT("RightHandMiddle1"));
	FVector BulletDir = (BulletDestination - PlayerRightHandDir).GetSafeNormal(); // Dir = End - Start

	DRAW_LINE_SingleFrame(PlayerRightHandDir, BulletDestination)

	//spawn bullet
	if (BulletClass)
	{
		FTransform Transform = Player->GetActorTransform();
		ASFA_Bullet* Bullet = GetWorld()->SpawnActor<ASFA_Bullet>(BulletClass, Transform);

		if (bIsAiming)
		{
			Bullet->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
			Bullet->SetBulletSpeed(10000.f);
		}

		Bullet->Initialize(BulletDir);
	}

	//play montage
	if (!Shoot_Montage) return;
	Player->GetMesh()->GetAnimInstance()->Montage_Play(Shoot_Montage);
}

void USFA_PlayerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateForceMove(DeltaTime);
}

void USFA_PlayerStateMachine::InitializePointers()
{
	Camera = Cast<ASFA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	Player = Cast<ASFA_Player>(GetOwner());
	InputHandler = Player->GetInputHandler();
	PlayerMovementComponent = Player->GetPlayerMovement();
}

void USFA_PlayerStateMachine::UpdateForceMove(float DeltaTime)
{
	if (!bIsDashing) Debug::PrintFixedLine("bIsDashing = FALSE", 556);
	Debug::PrintFixedLine("DashElapsedTime : " + FString::SanitizeFloat(DashElapsedTime), 557);

	//dash process test
	if (bIsDashing)
	{
		DashElapsedTime += DeltaTime;
		const float DashProgress = DashElapsedTime / DashTime;
		if (DashProgress > 1.f)
		{
			bIsDashing = false;
		}
		DashDirection.Normalize();
		const FVector Offset = DashDirection * (DashDistance * DeltaTime / DashTime);
		const FVector NewPos = Player->GetActorLocation() + Offset;
		Player->SetActorLocation(NewPos, true);
		Debug::PrintFixedLine(Offset.ToString(), 555);
	}
}
