#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "A_AttackInput.generated.h"

class AA_Weapon;
class AA_MainCamera;
class AA_Player;
class AA_GameMode;
class UBoxComponent;

UENUM(BlueprintType)
enum class ESF_ComboLevel : uint8
{
	None = 0				UMETA(DisplayName = "None"),
	Attack01 = 0			UMETA(DisplayName = "Attack01"),
	Attack02 = 0			UMETA(DisplayName = "Attack02"),
	Attack03 = 0			UMETA(DisplayName = "Attack03"),
	Attack04 = 0			UMETA(DisplayName = "Attack04"),
	Attack05 = 0			UMETA(DisplayName = "Attack05"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTERISK_API UA_AttackInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UA_AttackInput();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BeginShortRangeAttack();
	void EndShortRangeAttack();

	void BeginLongRangeAttack();
	void EndLongRangeAttack();

public:
	/// @brief �R���{���͎�t true : start , false : end
	UPROPERTY(BlueprintReadOnly)
		bool ComboAccept = false;
	UPROPERTY(BlueprintReadOnly)
		int ComboCount = 1;

public:
	/// @brief �R���{�̏�Ԃ�ݒ�
	/// @param InComboState 
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void SetComboState(const ESF_ComboLevel InComboState) { ComboState = InComboState; }
	
	/// @brief �R���{�̏�Ԃ��擾
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		ESF_ComboLevel GetComboState() { return ComboState; }

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* AttackMontage;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		UAnimInstance* AnimInstance;

	UFUNCTION(BlueprintCallable, Category = "Function")
		void StartCollision();
	UFUNCTION(BlueprintCallable, Category = "Function")
		void EndCollision();
	UFUNCTION(BlueprintCallable, Category = "Function")
		void StartCombo();
	UFUNCTION(BlueprintCallable, Category = "Function")
		void EndCombo();
	UFUNCTION(BlueprintCallable, Category = "Function")
		void ResetCombo();

protected:
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBoxComponent;
	UPROPERTY(BlueprintReadWrite)
		AA_Weapon* Weapon = nullptr;
	UFUNCTION(BlueprintCallable)
		AA_Weapon* GetWeapon() const { return Weapon; };

private:
	// @brief �R���{�̏��
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
		ESF_ComboLevel ComboState;

	// @brief �R���{�I��
	void ComboSelect();
private:
	//////////////////////////////////////// Get�֐�
	FORCEINLINE AA_GameMode* GetGameMode() const;
	FORCEINLINE AA_MainCamera* GetMainCamera() const;
	FORCEINLINE AA_Player* GetPlayerCharacter() const;
		
};
\