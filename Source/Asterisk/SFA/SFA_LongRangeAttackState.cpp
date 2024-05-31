#include "SFA_LongRangeAttackState.h"
#include "SFA_Player.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "../DebugHelpers.h"
USFA_LongRangeAttackState::USFA_LongRangeAttackState()
	:hitDamage(20)
{
	//SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//RootComponent = SphereComp;
	//SphereComp->SetCollisionProfileName("Projectile");
	//SphereComp->InitSphereRadius(20.0f);
	////SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	////SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	////SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	//SphereComp->OnComponentHit.AddDynamic(this, &USFA_LongRangeAttackState::OnHit);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &USFA_LongRangeAttackState::OnBeginOverlap);
	//InitialLifeSpan = 4.0f;

	//EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	//EffectComp->SetupAttachment(SphereComp);

	//MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	//MovementComp->InitialSpeed = 1000.0f;
	//MovementComp->bRotationFollowsVelocity = true;
	//MovementComp->bInitialVelocityInLocalSpace = true;
	//MovementComp->ProjectileGravityScale = 0.f;
}

void USFA_LongRangeAttackState::OnEnterState()
{
	Super::OnEnterState();

	//SphereComp->IgnoreActorWhenMoving(this, true);

	//// if (!IsValid(SF_Player)) return;
	//UE_LOG(LogTemp, Warning, TEXT("LongRange"));

	////GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::LongRangeAttack);

	////throw magic ball
	//{
	//	if (!MagicballBP) return;
	//	FVector HandLocation = GetPlayerCharacter()->GetMesh()->GetSocketLocation("Magicball");

	//	ASF_MainCamera* camera = GetGameMode()->GetMainCamera();
	//	FTransform SpawnTM = FTransform(camera->GetActorRotation(), HandLocation);
	//	//ASF_EnemyBase* enemy = GetGameMode()->GetNearestEnemy();
	//	//if (!IsValid(enemy))return;
	//	FActorSpawnParameters SpawnParams;
	//	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//	SpawnParams.Instigator = GetPlayerCharacter();

	//	GetWorld()->SpawnActor<AActor>(MagicballBP, SpawnTM, SpawnParams);
	//	Debug::PrintFixedLine("LongRangeAttack()", 999);
	//}
}

void USFA_LongRangeAttackState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
}

void USFA_LongRangeAttackState::OnExitState()
{
	Super::OnExitState();
}

void USFA_LongRangeAttackState::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void USFA_LongRangeAttackState::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//filter
	//if (OtherActor == nullptr || OtherActor == this) return;
	//if (OtherActor->IsA<ASFA_Player>()) return;

	////debug
	////DRAW_SPHERE(GetActorLocation());
	//if (OtherActor != nullptr && OtherActor != this)
	//{
	//	FString ActorName = OtherActor->GetName();
	//	//UE_LOG(LogTemp, Warning, TEXT("HitActor: %s"), *ActorName);
	//	Debug::Print(ActorName);
	//}

	//apply damage
	//ISF_DamageableInterface* damageInterface = Cast<ISF_DamageableInterface>(OtherActor);
	//if (damageInterface)
	//{
	//	damageInterface->GetDamage(hitDamage);

	//	//spawn explosion
	//	if (ParticleEffect)
	//	{
	//		FVector Location = GetActorLocation();
	//		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	//		UGameplayStatics::SpawnEmitterAtLocation(
	//			GetWorld(), ParticleEffect, Location, Rotation, true);

	//		this->Destroy();
	//	}
	//}
}
