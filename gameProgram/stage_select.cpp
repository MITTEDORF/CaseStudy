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
#include "title.h"

#include "inputKeyboard.h"
#include "inputPadX.h"

#include "character_player.h"

#include "equipment_choice.h"

#include "math_animation.h"

#include "equipment_choice_config.h"
#include "character_config.h"

#include "stage_select_conf.h"

#include "debugproc.h"

#include "configholder.h"

#include "sound.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BACK_X (163.0f)
#define BACK_Y (225.0f/3)

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
	// �T�E���h�̍Đ�
	//----------------------------
	m_sound->Play(CSound::SOUND_LABEL_SELECT);

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

		if(!backFrag)
			ObjectUpdate();

		//----------------------------
		// ����
		//----------------------------
		if(m_keyboard->GetTrigger(DIK_RETURN))
		{
			m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECT_ENTERSE);
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}

		if(m_padX != NULL)
		{
			if(m_padX->GetButtonPress(XINPUT_GAMEPAD_A))
			{
				m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECT_ENTERSE);
				m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
			}
		}
	}

	//----------------------------
	// ��ʑJ��
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		if(!backFrag)
		{
			CConfigHolder::Set(CONFIG_STAGE,nowSelectObject);
			CManager::SetNextPhase((CPhase*)new CEquipmentChoice);
		}
		else
		{
			CManager::SetNextPhase((CPhase*)new CTitle);
		}
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

	mesPol = CScene2D::Create(device, CImport::STAGE_SELECT_MESSAGE, CScene2D::POINT_CENTER, 1);
	mesPol->SetSize(951.0f, 81.0f);
	mesPol->SetPos(SCREEN_WIDTH/2, 50.0f);

	backTitle = CScene2D::Create(device, CImport::BUTTON_CLOSE, CScene2D::POINT_CENTER);
	backTitle->SetSize(BACK_X, BACK_Y);
	backTitle->SetPos(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.9f);
	backTitle->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
	backTitle->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
	backTitle->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
	backTitle->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));

	select_object[STAGE_DESERT]    =CScene2D::Create(device, CImport::STAGE_SELECT_DESERT, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_FOREST]    =CScene2D::Create(device, CImport::STAGE_SELECT_FOREST, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_GLACIER]   =CScene2D::Create(device, CImport::STAGE_SELECT_GLACIER, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_SAVANNAH]  =CScene2D::Create(device, CImport::STAGE_SELECT_SAVANNAH, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_WATERSIDE] =CScene2D::Create(device, CImport::STAGE_SELECT_WATERSIDE, CScene2D::POINT_CENTER, 1);

	for(int i=0;i<STAGE_MAX;i++)
	{
		select_object[i] ->SetSize(POL_SIZE[i]);
		select_object[i] ->SetPos(POL_POS[i]);
	}

	select_object[nowSelectObject]->SetSize(POL_SIZE[STAGE_FOREST]*1.2f);
	select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 20.0f);
}

//=============================================================================
// �I�u�W�F�N�g�̑I���X�V
//=============================================================================
void CStageSelect::SelectObjectUpdate()
{
	if(m_keyboard->GetTrigger(DIK_S))
	{
		if(!backFrag)
		{
			m_time=0;
			backFrag = true;
			select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
			select_object[nowSelectObject]->SetPos(POL_POS[nowSelectObject]);
			backTitle->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
			backTitle->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
			backTitle->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
			backTitle->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
			backTitle->SetSize(BACK_X * 1.25f, BACK_Y * 1.25f);

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

		}
	}
	else if(m_keyboard->GetTrigger(DIK_W))
	{
		if(backFrag)
		{
			m_time=0;
			backFrag = false;
			backTitle->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
			backTitle->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
			backTitle->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
			backTitle->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
			backTitle->SetRot(0);
			backTitle->SetSize(BACK_X, BACK_Y);

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

		}
	}

	if(m_padX != NULL)
	{
		if(m_padX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			if(!backFrag)
			{
				m_time=0;
				backFrag = true;
				select_object[nowSelectObject]->SetRot(0);
				select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
				select_object[nowSelectObject]->SetPos(POL_POS[nowSelectObject]);
				backTitle->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
				backTitle->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
				backTitle->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
				backTitle->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
				backTitle->SetSize(BACK_X * 1.25f, BACK_Y * 1.25f);
			}
			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );
		}

		if(m_padX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP))
		{
			if(backFrag)
			{
				m_time=0;
				backFrag = false;
				backTitle->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
				backTitle->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
				backTitle->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
				backTitle->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
				backTitle->SetRot(0);
				select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
				backTitle->SetSize(BACK_X, BACK_Y);
			}
			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );
		}
	}

	if(backFrag)
	{
		//�h�ꎞ�Ԃ𑝂₷
		m_time += SHAKING_SPD/2;
		//sin���g����rot�l���o
		float value = sinf(m_time) * SHAKING_WIDTH/2;
		//�h�炷
		backTitle->SetRot(value);
	}
	else
	{
		if(m_keyboard->GetTrigger(DIK_D))
		{

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

			m_time=0;
			select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
			select_object[nowSelectObject]->SetPos(POL_POS[nowSelectObject]);
			select_object[nowSelectObject]->SetRot(0);
			nowSelectObject++;
			if(nowSelectObject>=STAGE_MAX){nowSelectObject=0;}
			select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
			if(nowSelectObject == STAGE_GLACIER || nowSelectObject == STAGE_SAVANNAH)
				select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y + 10.0f);
			else
				select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 10.0f);
		}

		if(m_keyboard->GetTrigger(DIK_A))
		{

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

			m_time=0;
			select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
			select_object[nowSelectObject]->SetPos(POL_POS[nowSelectObject]);
			select_object[nowSelectObject]->SetRot(0);
			nowSelectObject--;
			if(nowSelectObject<=-1){nowSelectObject=STAGE_MAX-1;}
			select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
			if(nowSelectObject == STAGE_GLACIER || nowSelectObject == STAGE_SAVANNAH)
				select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y + 13.0f);
			else
				select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 13.0f);
		}

		if(m_padX != NULL)
		{
			if(m_padX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT))
			{
				m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

				m_time=0;
				select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
				select_object[nowSelectObject]->SetPos(POL_POS[nowSelectObject]);
				select_object[nowSelectObject]->SetRot(0);
				nowSelectObject++;
				if(nowSelectObject>=STAGE_MAX){nowSelectObject=0;}
				select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
				if(nowSelectObject == STAGE_GLACIER || nowSelectObject == STAGE_SAVANNAH)
					select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y + 10.0f);
				else
					select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 10.0f);
			}

			if(m_padX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT))
			{
				m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

				m_time=0;
				select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
				select_object[nowSelectObject]->SetPos(POL_POS[nowSelectObject]);
				select_object[nowSelectObject]->SetRot(0);
				nowSelectObject--;
				if(nowSelectObject<=-1){nowSelectObject=STAGE_MAX-1;}
				select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
				if(nowSelectObject == STAGE_GLACIER || nowSelectObject == STAGE_SAVANNAH)
					select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y + 13.0f);
				else
					select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 13.0f);
				}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CStageSelect::ObjectUpdate()
{
	//�h�ꎞ�Ԃ𑝂₷
	m_time += SHAKING_SPD;
	//sin���g����rot�l���o
	float value = sinf(m_time) * SHAKING_WIDTH;
	//�h�炷
	select_object[nowSelectObject]->SetRot(value);
}