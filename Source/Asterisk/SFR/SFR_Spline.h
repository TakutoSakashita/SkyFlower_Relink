#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFR_Spline.generated.h"

class USplineComponent;

UCLASS()
class ASTERISK_API ASFR_Spline : public AActor
{
	GENERATED_BODY()
	
public:	
	ASFR_Spline();

	///////////////// override function
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	///////////////// custom function
public:
	UFUNCTION(BlueprintCallable)
	FVector GetWorldLocationAtSpline(const float InDistance) const;
	UFUNCTION(BlueprintCallable)
	FRotator GetWorldRotationAtSpline(const float InDistance) const;

	UFUNCTION(BlueprintCallable)
	bool IsInEndPos(const float InDistance) const;

	///////////////// custom parameter
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineComponent;
};