#pragma once

#include "CoreMinimal.h"
#include "SFA_EnemyBase.h"
#include "SFA_Shooter.generated.h"

UCLASS()
class ASTERISK_API ASFA_Shooter : public ASFA_EnemyBase
{
	GENERATED_BODY()

public:
	ASFA_Shooter();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};
