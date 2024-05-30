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
	void StartMoveDash();
	void EndMoveDash();
	// ������ړ�����
	void StartMoveJump();
	void EndMoveJump();

	/********************AttackInput********************/
	// �ߋ����U��
	void BeginShortRangeAttack();
	void EndShortRangeAttack();
	// �������U��
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
