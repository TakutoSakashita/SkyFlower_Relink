// ==================================================
// Filename	:	SF_GameMode.h
// Author	:	22cu0115 坂下 拓人
//				22cu0105 小田島 稜人
// Description:Playerから送られてくる情報を受け取る
// Update	:	2024/04/08
//				2024/04/16 小田島 ヒットストップ処理
//				2024/04/16 小田島 ロックオン処理
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
	// ヒットストップ開始
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartHitStop(const float InHitStopSpeed, const float InHitStopTime);

	// プレイヤーに一番近い敵を取得
	//UFUNCTION(BlueprintCallable, Category = "GameMode")
	//ASF_EnemyBase* GetNearestEnemy() const;

private:
	// 敵を生成し、管理するコンポーネント
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