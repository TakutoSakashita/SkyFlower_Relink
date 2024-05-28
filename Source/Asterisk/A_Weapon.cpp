// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Weapon.h"
#include "A_Player.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelpers.h"

AA_Weapon::AA_Weapon()
{
	// ボックスコリジョンを作成し、設定
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollision"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AA_Weapon::BeginPlay()
{
	Super::BeginPlay();

	// ボックスコリジョンが有効であれば、当たり判定を追加する
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AA_Weapon::OnBeginOverlap);
	}
}

void AA_Weapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//filter
	if (OtherActor == nullptr || OtherActor == this) return;
	if (OtherActor->IsA<AA_Player>()) return;

	//UE_LOG(LogTemp, Warning, TEXT("ASF_WeaponBase : OnBeginOverlap"));
	Debug::Print("ASF_WeaponBase : OnBeginOverlap");

	//apply damage
	IA_DamageableInterface* damageInterface = Cast<IA_DamageableInterface>(OtherActor);
	if (damageInterface)
	{
		damageInterface->GetDamage(hitDamage);

		//spawn explosion
		if (ParticleEffect)
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, Rotation, true);

			DRAW_SPHERE(Location)
				//this->Destroy();
		}
	}
}

