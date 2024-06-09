// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_UserWidget.h"
#include "Components/Overlay.h"

void USFA_UserWidget::SetCrosshairVisibility(bool IsVisible) const
{
	if (Overlay_Crosshair)
	{
		if (IsVisible)
		{
			Overlay_Crosshair->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Overlay_Crosshair->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
