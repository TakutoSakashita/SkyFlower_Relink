#pragma once

#include "CoreMinimal.h"
#include "A_EnemyControllerBase.h"
#include "A_EnemyAttackerController.generated.h"

class UBoxComponent;
class AA_EnemyAttacker;

UCLASS()
class ASTERISK_API AA_EnemyAttackerController : public AA_EnemyControllerBase
{
	GENERATED_BODY()

public:
	AA_EnemyAttackerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		float TimeSinceLastAttack = 0.f;

	virtual void UpdateState(const float InDeltaTime) override;
	virtual void ChooseActionByState(const float InDeltaTime) override;

private:
	virtual void UpdateOnNormal(const float InDeltaTime) override;
	virtual void OnBeginAttack() override;
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) override;
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) override;
	virtual void OnEndAttack() override;
	virtual void OnBeginDead() override;
	virtual void UpdateOnDead(const float InDeltaTime) override;
	virtual void OnEndDead() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		AA_EnemyAttacker* A_EnemyAttacker;
};
