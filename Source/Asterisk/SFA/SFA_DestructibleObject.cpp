#include "SFA_Player.h"
#include "SFA_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SFA_DestructibleObject.h"

ASFA_DestructibleObject::ASFA_DestructibleObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASFA_DestructibleObject::BeginPlay()
{
	Super::BeginPlay();
}

void ASFA_DestructibleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASFA_DestructibleObject::DestroyObject()
{
	if (ASFA_GameMode* GameMode = Cast<ASFA_GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->ObjectDestroyed();
	}

	Destroy();
}

void ASFA_DestructibleObject::TakeDamage(AActor* Aggressor, float Damage)
{
	if (ASFA_Player* Player = Cast<ASFA_Player>(Aggressor))
	{
		Health -= Damage;
		if (Health <= 0.f)
		{
			Health = 0.f;
			DestroyObject();
		}
	}
}


