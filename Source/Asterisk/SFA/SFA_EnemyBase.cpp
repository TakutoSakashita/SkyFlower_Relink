// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_EnemyBase.h"

#include "SFA_Player.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"


// Sets default values
ASFA_EnemyBase::ASFA_EnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(70.f);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Sphere;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Sphere);
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	StaticMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Sphere);
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
		if (Health <= 0.f)
		{
			Health = 0.f;
			Die();
		}
	}
}

void ASFA_EnemyBase::Die()
{
	// 音再生
	if (DeathSound)
		UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);

	// play death effect
	if(DeathEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation(), GetActorRotation(),FVector(5));

	Destroy();
}
