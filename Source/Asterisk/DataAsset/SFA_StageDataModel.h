#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "SFA_StageDataModel.generated.h"

// enemy group
USTRUCT(BlueprintType)
struct FSFA_EnemyGroup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor/*ASF_EnemyBase*/> EnemyType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 EnemyCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EnemyPos;
};


//////////
// wave
USTRUCT(BlueprintType)
struct FSFA_WaveSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSFA_EnemyGroup> EnemyGroup;
};

///////////
/// stageInfo
USTRUCT(BlueprintType)
struct FSFA_StageInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSFA_WaveSetting> WaveSetting;
};

UCLASS()
class ASTERISK_API USFA_StageDataModel : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* StageDataTable;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<uint8, FSFA_StageInfo> StageDataMap;

public:
	UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true"))
	void LoadData();
};
