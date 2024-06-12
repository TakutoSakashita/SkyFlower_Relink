// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "SFA_IDamageable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASFA_Bullet::ASFA_Bullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(15.f);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASFA_Bullet::OnBeginOverlap);
	RootComponent = Sphere;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetupAttachment(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	Niagara->SetupAttachment(Sphere);

	InitialLifeSpan = 5.f;
}

// Called when the game starts or when spawned
void ASFA_Bullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASFA_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASFA_Bullet::Initialize(const FVector& Vector, AActor* Actor)
{
	Aggressor = Actor;
	ProjectileMovement->Velocity = Vector * ProjectileMovement->InitialSpeed;
	ProjectileMovement->Activate();
}

void ASFA_Bullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (OtherActor == Aggressor) return;
	
	if (ISFA_IDamageable* Damageable = Cast<ISFA_IDamageable>(OtherActor))
	{
		Damageable->TakeDamage(Aggressor, Damage);
	}

	// 音再生
	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),DeathSound,GetActorLocation(),GetActorRotation());
	// play effect
	if (DeathEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation(), GetActorRotation(),FVector(3));

	Destroy();
}

void ASFA_Bullet::SetBulletSpeed(const float Speed) const
{
	ProjectileMovement->InitialSpeed = Speed;
}
