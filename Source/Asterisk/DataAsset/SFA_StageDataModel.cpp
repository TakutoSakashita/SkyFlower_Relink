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

    // �f�[�^�e�[�u���̍s�̗v�f��z��Ŏ擾
    FPermissionListOwners RowNameList = StageDataTable->GetRowNames();
    // �s�̐��������[�v
    for (int i = 0; i < RowNameList.Num(); i++)
    {
        const FName RowName = RowNameList[i];

        // �P�s���̍\���̂��擾
        FSFA_StageInfo* TableRow = StageDataTable->FindRow<FSFA_StageInfo>(RowName, FString());

        // ���ۂɃQ�[����Ŏg���₷���悤�Ƀf�[�^�����H����
        FSFA_StageInfo StageInfo;
        StageInfo.WaveSetting = TableRow->WaveSetting;

        // Map�ɒǉ�����
        StageDataMap.Add(i, StageInfo);
    }

    // �f�[�^�A�Z�b�g�ɕҏW�t���O��ǉ�
    MarkPackageDirty();

    // �f�[�^�A�Z�b�g��ۑ��Ώۂɒǉ�
    PackagesToSave.Add(GetOutermost());

    // �֘A�A�Z�b�g��S�ĕۑ��iSourceControl�g�p���̓`�F�b�N�A�E�g���邩���b�Z�[�W�E�B���h�E���o���j
    // �t�@�C���ҏW�t���O�iDirty)���t���Ă���݂̂̂�ۑ��Ώۂɂ������̂ő�������true
    // �ۑ�����ۂɊm�F�̃��b�Z�[�W�E�B���h�E���o���Ȃ��ꍇ�͑�������false�ɂ���
    FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, true, true);

#endif
}
#undef LOCTEXT_NAMESPACE