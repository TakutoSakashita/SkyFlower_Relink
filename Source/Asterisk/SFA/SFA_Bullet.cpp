// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ASFA_Bullet::ASFA_Bullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(15.f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetupAttachment(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

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

void ASFA_Bullet::Initialize(const FVector& Vector) const
{
	ProjectileMovement->Velocity = Vector * ProjectileMovement->InitialSpeed;
	ProjectileMovement->Activate();
}

void ASFA_Bullet::SetBulletSpeed(const float Speed) const
{
	ProjectileMovement->InitialSpeed = Speed;
}

