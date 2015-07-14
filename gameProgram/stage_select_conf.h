//=============================================================================
//
// �I����ʂ̊e��ݒ��� [equipment_choice_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _STAGE_SELECT_CONFIG_H
#define _STAGE_SELECT_CONFIG_H
//=============================================================================
// �ݒ���
//=============================================================================

//�I�u�W�F�N�g�̃|���S���T�C�Y
const D3DXVECTOR2 POL_SIZE[5]={
								D3DXVECTOR2(327.0f,196.0f),
								D3DXVECTOR2(321.0f,190.0f),
								D3DXVECTOR2(343.0f,193.0f),
								D3DXVECTOR2(327.0f,196.0f),
								D3DXVECTOR2(327.0f,196.0f)};
//�I�u�W�F�N�g�̊e���W
const D3DXVECTOR2 POL_POS[5]={
								D3DXVECTOR2(517.0f,69.0f),
								D3DXVECTOR2(835.0f,270.0f),
								D3DXVECTOR2(697.0f,431.0f),
								D3DXVECTOR2(251.0f,431.0f),
								D3DXVECTOR2(159.0f,168.0f)};

//�X�e�[�W
typedef enum
{
	// ��ɔz�u������
	STAGE_DESERT = 0,
	// �E�ɔz�u������
	STAGE_WATERSIDE,
	// �E���ɔz�u������
	STAGE_GLACIER,
	// �����ɔz�u������
	STAGE_SAVANNAH,
	// ���ɔz�u������
	STAGE_FOREST,
	
	//�X�e�[�W�̐�
	STAGE_MAX

} StageObject;

#endif
