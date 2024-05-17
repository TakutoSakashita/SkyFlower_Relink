// ==================================================
// Filename	:	SF_MoveInput.h
// Author	:	22cu0115 坂下拓人
// Description: 移動の関数定義
// Notes:		例
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_MovementInput.generated.h"

//class ASF_GameMode;
//class ASF_MainCamera;
class ASF_Player;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYFLOWER_API USF_MovementInput : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USF_MovementInput();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void MoveForward(const float InValue);
	void MoveRight(const float InValue);
	void MoveJump();
	void MoveDash();

protected:
	// 振り向き速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotationSpeed = 8.0f;
	// ダッシュ速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float dashSpeed = 1500.0f;

	ASF_Player* m_pCharacter;

private:
	void CharacterRotate() const;
	void AddForce(const FVector InDirection);

	////////////////////////////////////////// Get関数
	//FORCEINLINE ASF_GameMode* GetGameMode() const;
	//
	//FORCEINLINE ASF_MainCamera* GetMainCamera() const;

	//FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
