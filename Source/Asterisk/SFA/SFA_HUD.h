// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SFA_HUD.generated.h"

class USFA_UserWidget;

/**
 * 
 */
UCLASS()
class ASTERISK_API ASFA_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SFA_UserWidgetClass;

	UPROPERTY()
	USFA_UserWidget* SFA_UserWidgetInstance;

public:
	USFA_UserWidget* GetUserWidget() const { return SFA_UserWidgetInstance; }
	void ShowCrosshair(bool bShow) const;
};
