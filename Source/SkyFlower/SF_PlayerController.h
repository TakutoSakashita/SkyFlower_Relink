// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SF_PlayerController.generated.h"


class ASF_Player;
class ASF_MainCamera;

UCLASS()
class SKYFLOWER_API ASF_PlayerController : public APlayerController
{
	GENERATED_BODY()

	ASF_PlayerController();

protected:
	virtual void BeginPlay() override;

	////////////////////////////////////////// 入力バインド処理
protected:

	virtual void SetupInputComponent() override;
private:
	/********************MovementInput********************/
	// 視点Y軸回転処理
	void LookUp(const float InValue);
	// 視点X軸回転処理
	void Turn(const float InValue);

	// 前方向移動処理
	void MoveForward(const float InValue);
	// 横方向移動処理
	void MoveRight(const float InValue);
	// 前方向にダッシュする
	void MoveDash();
	// 上方向移動処理
	void MoveJump();

	/********************AttackInput********************/
	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

	void HomingShoot();
	void LockOn();
	void LongRangeAttack();

	///////////////////////////// custom variable
protected:
	ASF_Player* m_pCharacter;
	ASF_MainCamera* m_pCamera;

public:
	UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	void SetPlayerCharacter(ASF_Player* const InPlayerCharacter) { m_pCharacter = InPlayerCharacter; }

	UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	void SetMainCamera(ASF_MainCamera* const InMainCamera) { m_pCamera = InMainCamera; }
};
