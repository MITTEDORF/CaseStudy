//*****************************************************************************
//
// �����I����ʐ���N���X [equipment_choice.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "equipment_choice.h"
#include "manager.h"
#include "fade.h"

#include "game.h"

#include "inputKeyboard.h"

#include "character_player.h"

#include "math_animation.h"

#include "equipment_choice_config.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// ������
//=============================================================================
HRESULT CEquipmentChoice::Init(LPDIRECT3DDEVICE9 device)
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
	// �o�[�W�����\��
	//----------------------------
	m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);

	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CEquipmentChoice::Uninit(void)
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
void CEquipmentChoice::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		CostumeChoice();
		VehicleChoice();
		CurUpdate();
		AnimUpdate();
		cosUpdate();
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
		CManager::SetNextPhase((CPhase*)new CGame((CostumeID)costume_id,(VehicleID)vehicle_id));
	}
}

//=============================================================================
// �`��
//=============================================================================
void CEquipmentChoice::Draw(void)
{
}

//=============================================================================
// �I�u�W�F�N�g������
//=============================================================================
void CEquipmentChoice::InitObject(LPDIRECT3DDEVICE9 device)
{
	bg=CScene2D::Create(device, CImport::MAKE_UI_SELECT_BACK, CScene2D::POINT_LEFTTOP,2);
	bg->SetSize(SCREEN_WIDTH , SCREEN_HEIGHT );
	bg->SetPos(0,0);

	//�v���C���[�̐���
	m_player=CPlayer::Create(device);
	m_player->SetPos(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.3f);
	m_player->SetSize(128.0f*2.f,128.0f*2.f);
	m_player->Assy_()->SetSize(m_player->GetSize());
	m_player->SetKeyboard(m_keyboard);
	m_player->Set_isGame(false);

	m_cos=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cos);

	m_ass=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass->SetPos(SCREEN_WIDTH * 0.3f, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass);

	m_cur=CScene2D::Create(device, CImport::MAKE_UI_SELECT_CUR, CScene2D::POINT_CENTER);
	m_cur->SetSize(320.f,210.f);
	m_cur->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cur);

	m_slotback=CScene2D::Create(device, CImport::MAKE_UI_SELECT_FRAME, CScene2D::POINT_CENTER);
	m_slotback->SetSize(721.f,496.f);
	m_slotback->SetPos(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f);
}

//=============================================================================
// ��蕨�̑I��
//=============================================================================
void CEquipmentChoice::VehicleChoice()
{
	if(m_cur->GetPos().y==CUR_BUTTOM)
	{
		if(m_keyboard->GetTrigger(DIK_LEFT))
		{
			vehicle_id--;
			if(vehicle_id<=VEHICLE_TRAM)
			{
				vehicle_id=VEHICLE_TRAM;
			}
			m_player->SetVehicleID((VehicleID)vehicle_id);
		}

		else if(m_keyboard->GetTrigger(DIK_RIGHT))
		{
			vehicle_id++;
			if(vehicle_id>=VEHICLE_MAX-1)
			{
				vehicle_id=VEHICLE_MAX-1;
			}
			m_player->SetVehicleID((VehicleID)vehicle_id);
		}
	}
}
//=============================================================================
// �R�X�`���[���̑I��
//=============================================================================
void CEquipmentChoice::CostumeChoice()
{
	if(m_cur->GetPos().y==CUR_UP)
	{
		if(m_keyboard->GetTrigger(DIK_LEFT))
		{
			costume_id--;
			if(costume_id<=COSTUME_NONE)
			{
				costume_id=COSTUME_NONE;
			}
			m_player->SetCostumeID((CostumeID)costume_id);
		}

		else if(m_keyboard->GetTrigger(DIK_RIGHT))
		{
			costume_id++;
			if(costume_id>=COSTUME_MAX-1)
			{
				costume_id=COSTUME_MAX-1;
			}
			m_player->SetCostumeID((CostumeID)costume_id);
		}
	}
}

void CEquipmentChoice::AnimUpdate()
{
	if(cntAnim>=10)
		{
			nowAnim++;
			if(nowAnim==5)
			{
				nowAnim=1;
			}

			SetAnim(4,nowAnim,1,1,m_cur);
			cntAnim=0;
		}
		cntAnim++;
}

void CEquipmentChoice::CurUpdate()
{
	if(m_keyboard->GetTrigger(DIK_UP))
	{
		m_cur->SetPosY(CUR_UP);
	}

	else if(m_keyboard->GetTrigger(DIK_DOWN))
	{
		m_cur->SetPosY(CUR_BUTTOM);
	}
}

void CEquipmentChoice::cosUpdate()
{
	m_cos->SetTex(m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT));
	m_ass->SetTex(m_player->ConsultationVehicleTexID());
}