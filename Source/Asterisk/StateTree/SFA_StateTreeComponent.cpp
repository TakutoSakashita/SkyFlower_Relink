#include "SFA_StateTreeComponent.h"

USFA_StateTreeComponent::USFA_StateTreeComponent()
{
}

void USFA_StateTreeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USFA_StateTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USFA_StateTreeComponent::SwitchStateTree(UStateTree* const InStateTree)
{
	StateTreeRef.SetStateTree(InStateTree);
	InitializeComponent();
}