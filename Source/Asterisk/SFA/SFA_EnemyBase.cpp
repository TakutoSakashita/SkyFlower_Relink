#include "SFA_EnemyBase.h"
#include "NiagaraComponent.h"
#include "SFA_Player.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"


ASFA_EnemyBase::ASFA_EnemyBase()
	: EnemyState(EASF_EnemyState::Normal)
	, EnemyParam()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(70.f);
	RootComponent = Sphere;
	Sphere->SetCollisionProfileName(FName(TEXT("EnemyPreset")));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Sphere);
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	StaticMesh->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Sphere);
	
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	Niagara->SetupAttachment(Sphere);
}

void ASFA_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASFA_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASFA_EnemyBase::TakeDamage(AActor* Aggressor, float Damage)
{
	if (ASFA_Player* player = Cast<ASFA_Player>(Aggressor))
	{
		//get damage from player's bullet, reduce enemy hp
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
	// play sound
	if (DeathSound)
		UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);

	// play death effect
	if(DeathEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation(), GetActorRotation(),FVector(5));

	Destroy();
}
