// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_LaserCollision.h"

#include "SFA_EnemyBase.h"
#include "SFA_IDamageable.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../DebugHelpers.h"

// Sets default values
ASFA_LaserCollision::ASFA_LaserCollision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(15.f);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASFA_LaserCollision::OnBeginOverlap);
	RootComponent = Sphere;
	Sphere->SetCollisionProfileName(FName(TEXT("BulletPreset")));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetupAttachment(Sphere);

	AActor::SetLifeSpan(1.f);
}

// Called when the game starts or when spawned
void ASFA_LaserCollision::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASFA_LaserCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void ASFA_LaserCollision::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (OtherActor == Aggressor) return;
	if (Cast<ASFA_LaserCollision>(OtherActor)) return;
	if (Cast<ASFA_EnemyBase>(OtherActor)) return;

	if (ISFA_IDamageable* Damageable = Cast<ISFA_IDamageable>(OtherActor))
	{
		Damageable->TakeDamage(Aggressor, Damage);
	}

	// play sound
	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), GetActorRotation());
	// play effect
	if (DeathEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation(), GetActorRotation(),
		                                         FVector(3));

	Debug::PrintFixedLine(" LASER COLLISION : " + OtherActor->GetName(), 111111);
}

void ASFA_LaserCollision::Initialize(AActor* AggressorActor, FVector MoveDirection, float MoveSpeed, float LifeSpan,
                                     float InitDamage)
{
	Aggressor = AggressorActor;
	if(Aggressor) SetActorLocation(Aggressor->GetActorLocation());
	Direction = MoveDirection.GetSafeNormal();
	Speed = MoveSpeed;
	SetLifeSpan(LifeSpan);
	Damage = InitDamage;
}


void ASFA_LaserCollision::Move()
{
	if (Direction == FVector::ZeroVector || Speed == 0.f) return;
	
	FVector PrePos = GetActorLocation();
	FVector RelativeLocation = Direction * Speed;

	SetActorLocation(PrePos + RelativeLocation, false);
}
