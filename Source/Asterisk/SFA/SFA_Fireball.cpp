// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_Fireball.h"



// Sets default values
ASFA_Fireball::ASFA_Fireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASFA_Fireball::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASFA_Fireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASFA_Fireball::ShootAllDirections()
{
	if (!ProjectileClass || MaxProjectiles <= 0) return;

	const FVector SpawnLocation = GetActorLocation();

	// Golden ratio to distribute points evenly on a sphere
	const float goldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2.0f;

	for (int i = 1; i <= MaxProjectiles; ++i)
	{
		float theta = FMath::Acos(1 - 2 * float(i) / float(MaxProjectiles + 1));  // θ angle
		float phi = 2 * PI * goldenRatio * float(i);  // φ angle

		float x = FMath::Sin(theta) * FMath::Cos(phi);
		float y = FMath::Sin(theta) * FMath::Sin(phi);
		float z = FMath::Cos(theta);

		FVector SpherePoint = FVector(x, y, z) * ShootingRadius;
		FVector ProjectileLocation = SpawnLocation + SpherePoint;

		FRotator ProjectileRotation = SpherePoint.Rotation();

		GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileLocation, ProjectileRotation);
	}
}



