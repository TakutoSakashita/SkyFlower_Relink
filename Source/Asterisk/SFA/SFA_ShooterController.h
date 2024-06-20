#pragma once

#include "CoreMinimal.h"
#include "SFA_EnemyControllerBace.h"
#include "SFA_ShooterController.generated.h"

class ASFA_Shooter;

UCLASS()
class ASTERISK_API ASFA_ShooterController : public ASFA_EnemyControllerBace
{
	GENERATED_BODY()

public:
	ASFA_ShooterController();

	////////////////////////////////////////////////// Override
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void UpdateOnNormal(const float InDeltaTime) override;
	virtual void OnBeginAttack() override;
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) override;
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) override;
	virtual void OnEndAttack() override;
	virtual void OnBeginDead() override;
	virtual void UpdateOnDead(const float InDeltaTime) override;
	virtual void OnEndDead() override;

	////////////////////////////////////////////////// Custom
private:
	UPROPERTY()
	ASFA_Shooter* OwnerShooter;
};
