#include "SFA_StageDataModel.h"

#if WITH_EDITOR
#include "FileHelpers.h"
#endif

#define LOCTEXT_NAMESPACE "TEST"

void USFA_StageDataModel::LoadData()
{
#if WITH_EDITORONLY_DATA

    if (StageDataTable == nullptr) return;
    if (!StageDataTable->GetRowStruct()->IsChildOf(FSFA_StageInfo::StaticStruct())) return;

    TArray<UPackage*> PackagesToSave;

    StageDataMap.Empty();

    // データテーブルの行の要素を配列で取得
    FPermissionListOwners RowNameList = StageDataTable->GetRowNames();
    // 行の数だけループ
    for (int i = 0; i < RowNameList.Num(); i++)
    {
        const FName RowName = RowNameList[i];

        // １行分の構造体を取得
        FSFA_StageInfo* TableRow = StageDataTable->FindRow<FSFA_StageInfo>(RowName, FString());

        // 実際にゲーム上で使いやすいようにデータを加工する
        FSFA_StageInfo StageInfo;
        StageInfo.WaveSetting = TableRow->WaveSetting;

        // Mapに追加する
        StageDataMap.Add(i, StageInfo);
    }

    // データアセットに編集フラグを追加
    MarkPackageDirty();

    // データアセットを保存対象に追加
    PackagesToSave.Add(GetOutermost());

    // 関連アセットを全て保存（SourceControl使用時はチェックアウトするかメッセージウィンドウを出す）
    // ファイル編集フラグ（Dirty)が付いてるもののみを保存対象にしたいので第一引数はtrue
    // 保存する際に確認のメッセージウィンドウを出さない場合は第二引数をfalseにする
    FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, true, true);

#endif
}
#undef LOCTEXT_NAMESPACE