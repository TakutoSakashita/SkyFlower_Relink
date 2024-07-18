#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SFA_StageEventManagerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventDelegate);

UCLASS()
class ASTERISK_API USFA_StageEventManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public: // [RINDERON] properties exposed to blueprint
	UPROPERTY(BlueprintAssignable, Category = "Dynamic Delegate Component")
	FEventDelegate OnBeginEventDispatcher;

	UPROPERTY(BlueprintAssignable, Category = "Dynamic Delegate Component")
	FEventDelegate OnEndEventDispatcher;

	UFUNCTION(BlueprintCallable)
	void OnBeginEvent();

	UFUNCTION(BlueprintCallable)
	void OnEndEvent();
};
