// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SFA_UserWidget.generated.h"

class UOverlay;
/**
 * 
 */
UCLASS()
class ASTERISK_API USFA_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCrosshairVisibility(bool IsVisible) const;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_Crosshair;
	
};
