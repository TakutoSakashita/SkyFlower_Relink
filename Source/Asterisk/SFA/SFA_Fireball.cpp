#include "SFA_Fireball.h"
#include "GameFramework/ProjectileMovementComponent.h"

// デフォルト値を設定
ASFA_Fireball::ASFA_Fireball()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// ゲーム開始時またはスポーン時に呼び出される
void ASFA_Fireball::BeginPlay()
{
	Super::BeginPlay();
}

// フレームごとに呼び出される
void ASFA_Fireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 全方向にプロジェクタイルを発射
void ASFA_Fireball::ShootAllDirections()
{
	//if (ProjectileClass || MaxProjectiles <= 0) return;
	//UE_LOG(LogTemp, Warning, TEXT("SSSSSSSSSSSSSSSSSSSSS"));
	const FVector SpawnLocation = GetActorLocation();
	const float goldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2.0f;

	for (int i = 1; i <= MaxProjectiles; ++i)
	{
		float theta = FMath::Acos(1 - 2 * float(i) / float(MaxProjectiles + 1));
		float phi = 2 * PI * goldenRatio * float(i);

		float x = FMath::Sin(theta) * FMath::Cos(phi);
		float y = FMath::Sin(theta) * FMath::Sin(phi);
		float z = FMath::Cos(theta);

		FVector SpherePoint = FVector(x, y, z) * ShootingRadius;
		FVector ProjectileLocation = SpawnLocation + SpherePoint;
		FRotator ProjectileRotation = SpherePoint.Rotation();

		GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileLocation, ProjectileRotation);
	}
}
