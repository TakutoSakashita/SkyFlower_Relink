#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "SFA_StateTreeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTERISK_API USFA_StateTreeComponent : public UStateTreeComponent
{
	GENERATED_BODY()
	
public:
	USFA_StateTreeComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "SFA_StateTree")
	void SwitchStateTree(UStateTree* const InStateTree);
};