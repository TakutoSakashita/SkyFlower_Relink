#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "A_GameMode.generated.h"

//class USF_EnemyManager;
class AA_Player;
class AA_MainCamera;

UCLASS()
class ASTERISK_API AA_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AA_GameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	// ヒットストップ開始
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void StartHitStop(const float InHitStopSpeed, const float InHitStopTime);

	//// プレイヤーに一番近い敵を取得
	//UFUNCTION(BlueprintCallable, Category = "GameMode")
	//	ASF_EnemyBase* GetNearestEnemy() const;

private:
	//// 敵を生成し、管理するコンポーネント
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	//	USF_EnemyManager* EnemyManager;

	UPROPERTY(VisibleAnywhere, Category = "GameMode")
		AA_Player* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, Category = "GameMode")
		AA_MainCamera* MainCamera;

	//UPROPERTY(VisibleAnywhere, Category = "GameMode")
	//	ASF_EnemyBase* LockOnEnemy;

public:
	//USF_EnemyManager* GetEnemyManager() const { return EnemyManager; }

	void SetPlayerCharacter(AA_Player* const InPlayerCharacter) { PlayerCharacter = InPlayerCharacter; }
	void SetMainCamera(AA_MainCamera* const InMainCamera) { MainCamera = InMainCamera; }

	UFUNCTION(BlueprintCallable, Category = "A_GameMode")
		AA_Player* GetPlayerCharacter() const { return PlayerCharacter; }
	UFUNCTION(BlueprintCallable, Category = "A_GameMode")
		AA_MainCamera* GetMainCamera() const { return MainCamera; }

	//void SetLockOnEnemy(ASF_EnemyBase* const InEnemy) { LockOnEnemy = InEnemy; }
	//UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	//	ASF_EnemyBase* GetLockOnEnemy() const { return LockOnEnemy; }

private:
	// ヒットストップ中か
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
		bool bIsInHitStop;
	// ヒットストップの速度
	UPROPERTY(EditAnywhere, Category = "HitStop | Edit")
		float HitStopSpeed;
	// ヒットストップの時間
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
		float HitStopTime;
	// ヒットストップタイマー用
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
		float Timer_HitStop;
};
