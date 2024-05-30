// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "A_PlayerController.generated.h"


class AA_Player;
class AA_MainCamera;

UCLASS()
class ASTERISK_API AA_PlayerController : public APlayerController
{
	GENERATED_BODY()

		AA_PlayerController();


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
	void StartMoveDash();
	void EndMoveDash();
	// 上方向移動処理
	void StartMoveJump();
	void EndMoveJump();

	/********************AttackInput********************/
	// 近距離攻撃
	void BeginShortRangeAttack();
	void EndShortRangeAttack();
	// 遠距離攻撃
	void BeginLongRangeAttack();
	void EndLongRangeAttack();
	//
	void HomingAttack();
	void HomingShoot();
	void LaserAttack();
	//
	void LockOn();

	///////////////////////////// custom variable
protected:
	AA_Player* m_pCharacter;
	AA_MainCamera* m_pCamera;

public:
	UFUNCTION(BlueprintCallable, Category = "A_GameMode")
		void SetPlayerCharacter(AA_Player* const InPlayerCharacter) { m_pCharacter = InPlayerCharacter; }

	UFUNCTION(BlueprintCallable, Category = "A_GameMode")
		void SetMainCamera(AA_MainCamera* const InMainCamera) { m_pCamera = InMainCamera; }
};
