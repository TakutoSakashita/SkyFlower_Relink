// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_EnemyBase.h"

// Sets default values
ASFA_EnemyBase::ASFA_EnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ASFA_EnemyBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASFA_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASFA_EnemyBase::TakeDamage(AActor* Aggressor, float Damage)
{
	if (ASFA_Player* player = Cast<ASFA_Player>(Aggressor))
	{
		//get damage from player, reduce enemy hp
		Health -= Damage;
		if (Health <= 0.f) {
			Health = 0.f;
			Die();
		}
	}

}

void ASFA_EnemyBase::Die()
{
	// ‰¹Ä¶
	//UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
}

