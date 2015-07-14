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
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f)};
//�I�u�W�F�N�g�̊e���W
const D3DXVECTOR2 POL_POS[5]={
								D3DXVECTOR2(672.0f,105.0f),
								D3DXVECTOR2(992.0f,262.0f),
								D3DXVECTOR2(855.0f,469.0f),
								D3DXVECTOR2(406.0f,469.0f),
								D3DXVECTOR2(312.0f,217.0f)};

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
