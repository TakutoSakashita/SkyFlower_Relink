// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_InputHandlerComponent.h"
#include "DebugHelpers.h"
#include "SFR_MoveComponent.h"
#include "SFR_ActionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SFR_PlayerController.h"
#include "SFR_PlayerCamera.h"
#include "SFR_Player.h"


USFR_InputHandlerComponent::USFR_InputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USFR_InputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USFR_InputHandlerComponent::Initialize(AActor* player)
{
	if (!IsValid(player)) return;

	Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();
	ensure(Camera);

	Player = Cast<ASFR_Player>(player);
	ensure(Player);

	MoveComponent = Player->MoveComponent;
	ActionComponent = Player->ActionComponent;
}

void USFR_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Debug::Print("USFR_InputHandlerComponent::SetupPlayerInputComponent");

	PlayerInputComponent->BindAxis("MoveForward", this, &USFR_InputHandlerComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &USFR_InputHandlerComponent::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &USFR_InputHandlerComponent::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &USFR_InputHandlerComponent::LookUp);




}


// Called every frame
void USFR_InputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Debug::PrintFixedLine("USFR_InputHandlerComponent::TickComponent", 101);

	if (!IsValid(Camera))
		Camera = Cast<ASFR_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetCamera();

}




void USFR_InputHandlerComponent::MoveForward(float Value)
{
	if (!IsValid(MoveComponent)) return;
	//MoveComponent->MoveForward(Value);
}

void USFR_InputHandlerComponent::MoveRight(float Value)
{
	if (!IsValid(MoveComponent)) return;
	//MoveComponent->MoveRight(Value);
}

void USFR_InputHandlerComponent::Turn(float Value)
{
	if (!IsValid(Camera)) return;

	Camera->Turn(Value);
}

void USFR_InputHandlerComponent::LookUp(float Value)
{
	if (!IsValid(Camera)) return;

	Camera->LookUp(Value);
}
