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
	void MoveAcceleration(const float InValue);
	// 横方向移動処理
	void MoveRight(const float InValue);
	// 前方向にダッシュする
	void MoveDash();
	void StopMoveDash();
	// 上方向移動処理
	void MoveJump();

	/********************AttackInput********************/
	void BeginShortRangeAttack();
	void EndShortRangeAttack();
	void HomingAttack();
	void LaserAttack();

	void HomingShoot();
	void LockOn();
	void BeginLongRangeAttack();
	void EndLongRangeAttack();

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
