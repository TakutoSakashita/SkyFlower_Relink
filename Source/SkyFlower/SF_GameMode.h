// ==================================================
// Filename	:	SF_GameMode.h
// Author	:	22cu0115 �≺ ��l
//				22cu0105 ���c�� �Ől
// Description:Player���瑗���Ă�������󂯎��
// Update	:	2024/04/08
//				2024/04/16 ���c�� �q�b�g�X�g�b�v����
//				2024/04/16 ���c�� ���b�N�I������
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SF_GameMode.generated.h"

//class USF_EnemyManager;
class ASF_Player;
//class ASF_MainCamera;

UCLASS()
class SKYFLOWER_API ASF_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASF_GameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	// �q�b�g�X�g�b�v�J�n
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartHitStop(const float InHitStopSpeed, const float InHitStopTime);

	// �v���C���[�Ɉ�ԋ߂��G���擾
	//UFUNCTION(BlueprintCallable, Category = "GameMode")
	//ASF_EnemyBase* GetNearestEnemy() const;

private:
	// �G�𐶐����A�Ǘ�����R���|�[�l���g
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	//USF_EnemyManager* EnemyManager;

	UPROPERTY(VisibleAnywhere, Category = "GameMode")
	ASF_Player* PlayerCharacter;

	//UPROPERTY(VisibleAnywhere, Category = "GameMode")
	//ASF_MainCamera* MainCamera;
	//
	//UPROPERTY(VisibleAnywhere, Category = "GameMode")
	//ASF_EnemyBase* LockOnEnemy;

public:
	void SetPlayerCharacter(ASF_Player* const InPlayerCharacter) { PlayerCharacter = InPlayerCharacter; }
	//USF_EnemyManager* GetEnemyManager() const { return EnemyManager; }
	//
	//void SetMainCamera(ASF_MainCamera* const InMainCamera) { MainCamera = InMainCamera; }
	//
	//UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	//ASF_Player* GetPlayerCharacter() const { return PlayerCharacter; }
	//UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	//ASF_MainCamera* GetMainCamera() const { return MainCamera; }
	//
	//void SetLockOnEnemy(ASF_EnemyBase* const InEnemy) { LockOnEnemy = InEnemy; }
	//UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	//ASF_EnemyBase* GetLockOnEnemy() const { return LockOnEnemy; }

private:
	// �q�b�g�X�g�b�v����
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	bool bIsInHitStop;
	// �q�b�g�X�g�b�v�̑��x
	UPROPERTY(EditAnywhere, Category = "HitStop | Edit")
	float HitStopSpeed;
	// �q�b�g�X�g�b�v�̎���
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	float HitStopTime;
	// �q�b�g�X�g�b�v�^�C�}�[�p
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	float Timer_HitStop;
};