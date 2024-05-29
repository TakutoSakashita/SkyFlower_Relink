#include "SFR_Spline.h"
#include "Components/SplineComponent.h"

ASFR_Spline::ASFR_Spline()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void ASFR_Spline::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASFR_Spline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// @brief 進んだ距離からスプライン上の座標を取得する
/// @param InDistance 進んだ距離
/// @return 
FVector ASFR_Spline::GetWorldLocationAtSpline(const float InDistance) const
{
	if (!IsValid(SplineComponent)) return FVector(0.f);

	return SplineComponent->GetLocationAtDistanceAlongSpline(InDistance, ESplineCoordinateSpace::World);
}

/// @brief 進んだ距離からスプライン上の角度を取得する
/// @param InDistance 進んだ距離
/// @return 
FRotator ASFR_Spline::GetWorldRotationAtSpline(const float InDistance) const
{
	if(!IsValid(SplineComponent)) return FRotator(0.f);

	return SplineComponent->GetRotationAtDistanceAlongSpline(InDistance, ESplineCoordinateSpace::World);
}

/// @brief 終着点に到達したかチェックする
/// @param InDistance 進んだ距離
/// @return 
bool ASFR_Spline::IsInEndPos(const float InDistance) const
{
	if (!IsValid(SplineComponent)) return false;

	return InDistance > SplineComponent->GetSplineLength();
}