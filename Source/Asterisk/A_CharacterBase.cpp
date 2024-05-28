#include "A_CharacterBase.h"
#include "DebugHelpers.h"

AA_CharacterBase::AA_CharacterBase()
	: CharacterState(ESF_CharacterState::None)
	, CharacterParam(FSF_CharacterInfo())
	, CurrentHP(0.f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// èâä˙âª
	CharacterState = ESF_CharacterState::Normal;
	CurrentHP = CharacterParam.MaxHP;
}

void AA_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void AA_CharacterBase::GetDamage(int32 damage)
//{
//	Debug::PrintFixedLine("GetDamage CharacterBase");
//}
