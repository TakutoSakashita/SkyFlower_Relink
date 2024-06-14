// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_Weapon.h"
#include "SFA_Player.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "../DebugHelpers.h"

// Sets default values
ASFA_Weapon::ASFA_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ボックスコリジョンを作成し、設定
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollision"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASFA_Weapon::BeginPlay()
{
	Super::BeginPlay();

	Aggressor = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	// ボックスコリジョンが有効であれば、当たり判定を追加する
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASFA_Weapon::OnBeginOverlap);
	}
}

// Called every frame
void ASFA_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASFA_Weapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//filter
	if (OtherActor == nullptr || OtherActor == this) return;
	if (OtherActor->IsA<ASFA_Player>()) return;
	if (OtherActor == Aggressor) return;
	
	if (ISFA_IDamageable* Damageable = Cast<ISFA_IDamageable>(OtherActor))
	{
		Damageable->TakeDamage(Aggressor, hitDamage);
	}

	// play sound
	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),DeathSound,GetActorLocation(),GetActorRotation());
	// play effect
	if (ParticleEffect)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, Rotation, true);

		DRAW_SPHERE(Location)
			//this->Destroy();
	}

	
	//UE_LOG(LogTemp, Warning, TEXT("ASF_WeaponBase : OnBeginOverlap"));
	Debug::Print("ASF_WeaponBase : OnBeginOverlap");
}

