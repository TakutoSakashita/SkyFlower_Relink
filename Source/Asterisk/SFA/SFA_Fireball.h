#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFA_Fireball.generated.h"

class UProjectileMovementComponent;

UCLASS()
class ASTERISK_API ASFA_Fireball : public AActor
{
	GENERATED_BODY()

public:
	ASFA_Fireball();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<class AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	int32 MaxProjectiles = 30; // 発射する弾の最大数

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootingAngleIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootingRadius;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ShootAllDirections();
};
