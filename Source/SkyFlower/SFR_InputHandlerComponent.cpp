// Fill out your copyright notice in the Description page of Project Settings.


#include "SFR_InputHandlerComponent.h"
#include "DebugHelpers.h"
#include "SFR_MoveComponent.h"
#include "SFR_ActionComponent.h"

// Sets default values for this component's properties
USFR_InputHandlerComponent::USFR_InputHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USFR_InputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USFR_InputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Debug::Print("USFR_InputHandlerComponent::SetupPlayerInputComponent");
}



// Called every frame
void USFR_InputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USFR_InputHandlerComponent::Initialize(AActor* player)
{
	if (!IsValid(player)) return;
	MoveComponent = NewObject<USFR_MoveComponent>(player);
	if (MoveComponent)
	{
		MoveComponent->RegisterComponent();
		player->AddInstanceComponent(MoveComponent);
	}

	ActionComponent = NewObject<USFR_ActionComponent>(player);
	if (ActionComponent)
	{
		ActionComponent->RegisterComponent();
		player->AddInstanceComponent(ActionComponent);
	}
}