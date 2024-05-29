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

/// @brief �i�񂾋�������X�v���C����̍��W���擾����
/// @param InDistance �i�񂾋���
/// @return 
FVector ASFR_Spline::GetWorldLocationAtSpline(const float InDistance) const
{
	if (!IsValid(SplineComponent)) return FVector(0.f);

	return SplineComponent->GetLocationAtDistanceAlongSpline(InDistance, ESplineCoordinateSpace::World);
}

/// @brief �i�񂾋�������X�v���C����̊p�x���擾����
/// @param InDistance �i�񂾋���
/// @return 
FRotator ASFR_Spline::GetWorldRotationAtSpline(const float InDistance) const
{
	if(!IsValid(SplineComponent)) return FRotator(0.f);

	return SplineComponent->GetRotationAtDistanceAlongSpline(InDistance, ESplineCoordinateSpace::World);
}

/// @brief �I���_�ɓ��B�������`�F�b�N����
/// @param InDistance �i�񂾋���
/// @return 
bool ASFR_Spline::IsInEndPos(const float InDistance) const
{
	if (!IsValid(SplineComponent)) return false;

	return InDistance > SplineComponent->GetSplineLength();
}