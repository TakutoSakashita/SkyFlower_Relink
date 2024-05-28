#include "A_AttackInput.h"

// for normal attack
#include "A_Player.h"
#include "A_GameMode.h"
#include "A_Weapon.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "DebugHelpers.h"

// for homing attack
#include "Kismet/GameplayStatics.h"
#include "A_MainCamera.h"
//#include "A_FunctionLibrary.h"
//#include "A_HomingMagicball.h"
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "Math/RotationMatrix.h"
#include "EngineUtils.h"  

// Sets default values for this component's properties
UA_AttackInput::UA_AttackInput()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComboState(ESF_ComboLevel::None);
}


// Called when the game starts
void UA_AttackInput::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UA_AttackInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UA_AttackInput::BeginShortRangeAttack()
{
	// ComboMontageはAnimMontageへのポインタを保持している変数です
	AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (ComboAccept)
	{
		ComboCount++;
	}

	if (AttackMontage && AnimInstance)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ComboMontage"));

		FString SectionName = FString::Printf(TEXT("Attack0%d"), ComboCount);
		FName SectionFName(*SectionName);
		
		GetPlayerCharacter()->PlayAnimMontage(AttackMontage, 1.0f, SectionFName);
		if (!AnimInstance->Montage_IsPlaying(AttackMontage))
		{
		}
	}
}

void UA_AttackInput::EndShortRangeAttack()
{

}

void UA_AttackInput::BeginLongRangeAttack()
{

}

void UA_AttackInput::EndLongRangeAttack()
{

}

///////////////// NotifyEvent /////////////////
// →AnimMontageからプレイヤーのアニメーションBPで通知を受け取る
// →アニメーションBPからAttackInputの関数呼び出し
void UA_AttackInput::StartCollision()
{
	if (!Weapon)
	{
		Weapon = Cast<AA_Weapon>
			(UGameplayStatics::GetActorOfClass(GetWorld(), AA_Weapon::StaticClass()));
	}

	if (!CollisionBoxComponent)
	{
		CollisionBoxComponent = Weapon->GetBoxComponent();
	}
	
	if (!Weapon) return;
	if (!CollisionBoxComponent)return;

	// コリジョンを有効にする
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UA_AttackInput::EndCollision()
{
	if (!CollisionBoxComponent)return;

	// コリジョンを無効にする
	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UA_AttackInput::StartCombo()
{
	ComboAccept = true;
}

void UA_AttackInput::EndCombo()
{
	ComboAccept = false;
}

void UA_AttackInput::ResetCombo()
{
	ComboCount = 1;
	ComboAccept = false;
}
///////////////// NotifyEvent /////////////////

void UA_AttackInput::ComboSelect()
{
	switch (ComboCount)
	{
	case 0 :
		SetComboState(ESF_ComboLevel::None);
		break;

	case 1:
		SetComboState(ESF_ComboLevel::Attack01);
		break;

	case 2:
		SetComboState(ESF_ComboLevel::Attack02);
		break;

	case 3:
		SetComboState(ESF_ComboLevel::Attack03);
		break;

	case 4:
		SetComboState(ESF_ComboLevel::Attack04);
		break;

	case 5:
		SetComboState(ESF_ComboLevel::Attack05);
		break;
	default:
		break;
	}
}

///////////////////////////FORCEINLINE
AA_GameMode* UA_AttackInput::GetGameMode() const
{
	return Cast<AA_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

AA_MainCamera* UA_AttackInput::GetMainCamera() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetMainCamera();
}

AA_Player* UA_AttackInput::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}