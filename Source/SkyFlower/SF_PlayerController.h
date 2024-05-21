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

	////////////////////////////////////////// ���̓o�C���h����
protected:

	virtual void SetupInputComponent() override;
private:
	/********************MovementInput********************/
	// ���_Y����]����
	void LookUp(const float InValue);
	// ���_X����]����
	void Turn(const float InValue);

	// �O�����ړ�����
	void MoveForward(const float InValue);
	// �������ړ�����
	void MoveRight(const float InValue);
	// �O�����Ƀ_�b�V������
	void MoveDash();
	// ������ړ�����
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
