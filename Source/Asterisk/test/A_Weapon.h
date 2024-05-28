#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Weapon.generated.h"

class UBoxComponent;

UCLASS()
class ASTERISK_API AA_Weapon : public AActor
{
	GENERATED_BODY()

public:
	AA_Weapon();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		float hitDamage = 20;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxComponent;

public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "TEST")
		UParticleSystem* ParticleEffect;

	UBoxComponent* GetBoxComponent() { return BoxComponent; }

};
