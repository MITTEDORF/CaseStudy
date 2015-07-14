//*****************************************************************************
//
// �X�e�[�W�I����ʐ���N���X [stage_selrect.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stage_select.h"
#include "manager.h"
#include "fade.h"

#include "game.h"

#include "inputKeyboard.h"

#include "character_player.h"

#include "equipment_choice.h"

#include "math_animation.h"

#include "equipment_choice_config.h"
#include "character_config.h"

#include "stage_select_conf.h"

#include "debugproc.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// ������
//=============================================================================
HRESULT CStageSelect::Init(LPDIRECT3DDEVICE9 device)
{
	//�ϐ���NULL����
	NullSetVariable();
	//----------------------------
	// �f�o�C�X�擾
	//----------------------------
	m_device = device;

	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------
	InitObject(device);

	//----------------------------
	// �t�F�[�h
	//----------------------------
	m_fade = CFade::Create(device);
	m_fade->Start(CFade::FADESTATE_IN, 1, 1.0f, 1.0f, 1.0f, 1.0f);

	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CStageSelect::Uninit(void)
{
	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------
	// �V�[��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V
//=============================================================================
void CStageSelect::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{

		SelectObjectUpdate();

		//----------------------------
		// ����
		//----------------------------
		if(m_keyboard->GetTrigger(DIK_RETURN))
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

	//----------------------------
	// ��ʑJ��
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		CManager::SetNextPhase((CPhase*)new CEquipmentChoice);
	}
}

//=============================================================================
// �`��
//=============================================================================
void CStageSelect::Draw(void)
{

}

//=============================================================================
// �I�u�W�F�N�g������
//=============================================================================
void CStageSelect::InitObject(LPDIRECT3DDEVICE9 device)
{
	//�w�i�̐���
	select_bg = CScene2D::Create(device, CImport::STAGE_SELECT_BG, CScene2D::POINT_LEFTTOP, 1);
	select_bg ->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	select_bg ->SetPos(0.0f, 0.0f);

	
	select_object[STAGE_DESERT]    =CScene2D::Create(device, CImport::STAGE_SELECT_DESERT, CScene2D::POINT_LEFTTOP, 1);
	select_object[STAGE_FOREST]    =CScene2D::Create(device, CImport::STAGE_SELECT_FOREST, CScene2D::POINT_LEFTTOP, 1);
	select_object[STAGE_GLACIER]   =CScene2D::Create(device, CImport::STAGE_SELECT_GLACIER, CScene2D::POINT_LEFTTOP, 1);
	select_object[STAGE_SAVANNAH]  =CScene2D::Create(device, CImport::STAGE_SELECT_SAVANNAH, CScene2D::POINT_LEFTTOP, 1);
	select_object[STAGE_WATERSIDE] =CScene2D::Create(device, CImport::STAGE_SELECT_WATERSIDE, CScene2D::POINT_LEFTTOP, 1);

	for(int i=0;i<STAGE_MAX;i++)
	{
		select_object[i] ->SetSize(POL_SIZE[i]);
		select_object[i] ->SetPos(POL_POS[i]);
	}

}

//=============================================================================
// �I�u�W�F�N�g�̑I���X�V
//=============================================================================
void CStageSelect::SelectObjectUpdate()
{
	if(m_keyboard->GetTrigger(DIK_RIGHT))
	{
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
		nowSelectObject++;
		if(nowSelectObject>=STAGE_MAX){nowSelectObject=0;}
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
	}

	if(m_keyboard->GetTrigger(DIK_LEFT))
	{
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
		nowSelectObject--;
		if(nowSelectObject<=-1){nowSelectObject=STAGE_MAX-1;}
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
	}
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CStageSelect::ObjectUpdate()
{

}