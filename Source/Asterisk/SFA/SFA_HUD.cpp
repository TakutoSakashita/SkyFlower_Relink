// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_HUD.h"
#include "Blueprint/UserWidget.h"
#include "SFA_UserWidget.h"

void ASFA_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (SFA_UserWidgetClass != nullptr)
	{
		SFA_UserWidgetInstance = CreateWidget<USFA_UserWidget>(GetWorld(), SFA_UserWidgetClass);

		if (SFA_UserWidgetInstance != nullptr)
		{
			SFA_UserWidgetInstance->AddToViewport();
		}
	}
}

void ASFA_HUD::ShowCrosshair(const bool bShow) const
{
	if (SFA_UserWidgetInstance)
	{
		SFA_UserWidgetInstance->SetCrosshairVisibility(bShow);
	}
}
