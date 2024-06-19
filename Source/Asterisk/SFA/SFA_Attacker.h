#pragma once

#include "CoreMinimal.h"
#include "SFA_EnemyBase.h"
#include "SFA_Attacker.generated.h"

UCLASS()
class ASTERISK_API ASFA_Attacker : public ASFA_EnemyBase
{
	GENERATED_BODY()

public:
	ASFA_Attacker();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};