#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "A_DamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UA_DamageableInterface : public UInterface
{
	GENERATED_BODY()
};

class ASTERISK_API IA_DamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetDamage(int32 damage) = 0;
};
