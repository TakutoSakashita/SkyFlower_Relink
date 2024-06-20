#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SFA_EnemyControllerBace.generated.h"

UCLASS()
class ASTERISK_API ASFA_EnemyControllerBace : public AAIController
{
	GENERATED_BODY()

public:
	ASFA_EnemyControllerBace();
	
	////////////////////////////////////////////////// Override
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	////////////////////////////////////////////////// Custom
protected:
	virtual void UpdateOnNormal(const float InDeltaTime) {};
	virtual void OnBeginAttack() {};
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) {};
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) {};
	virtual void OnEndAttack() {};
	virtual void OnBeginDead() {};
	virtual void UpdateOnDead(const float InDeltaTime) {};
	virtual void OnEndDead() {};
};
