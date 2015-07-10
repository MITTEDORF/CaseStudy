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

	cosUpdate(0);
	cosUpdate(1);
	cosUpdate(2);

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

		cosUpdate(0);
		cosUpdate(1);
		cosUpdate(2);

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
	m_player->SetPos(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f);
	m_player->SetSize(128.0f*2.5f,128.0f*2.5f);
	m_player->Assy_()->SetSize(m_player->GetSize());
	m_player->SetKeyboard(m_keyboard);
	m_player->Set_isGame(false);

	float PolSize=m_player->GetSize().x/1.5f;

	m_cos[0]=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos[0]->SetPos(SCREEN_WIDTH * 0.3f-PolSize, CUR_UP);
	SetAnim(4,1,1,1,m_cos[0]);

	m_ass[0]=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass[0]->SetPos(SCREEN_WIDTH * 0.3f-PolSize, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass[0]);

	m_cos[1]=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos[1]->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cos[1]);

	m_ass[1]=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass[1]->SetPos(SCREEN_WIDTH * 0.3f, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass[1]);

	m_cos[2]=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos[2]->SetPos(SCREEN_WIDTH * 0.3f+PolSize, CUR_UP);
	SetAnim(4,1,1,1,m_cos[2]);

	m_ass[2]=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass[2]->SetPos(SCREEN_WIDTH * 0.3f+PolSize, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass[2]);

	m_cur=CScene2D::Create(device, CImport::MAKE_UI_SELECT_CUR, CScene2D::POINT_CENTER);
	m_cur->SetSize(320.f,210.f);
	m_cur->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cur);

	m_slotback=CScene2D::Create(device, CImport::MAKE_UI_SELECT_FRAME, CScene2D::POINT_CENTER);
	m_slotback->SetSize(721.f,496.f);
	m_slotback->SetPos(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f);

	// ���ʃe�L�X�g
	m_message = CScene2D::Create(device, CImport::MAKE_UI_VEH_MES_SLED, CScene2D::POINT_CENTER);
	m_message->SetSize(1200.0f,91.0f);
	m_message->SetPos(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9);
	// ���ʃE�B���h�E
	m_message_win = CScene2D::Create(device, CImport::MAKE_UI_COS_DETAIL, CScene2D::POINT_CENTER,2);
	m_message_win->SetSize(1200.0f,91.0f);
	m_message_win->SetPos(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9);

	// ��蕨���e�L�X�g
	m_veh_mes = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_5, CScene2D::POINT_CENTER);
	m_veh_mes->SetSize(466.0f,91.0f);
	m_veh_mes->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55);
	// ��蕨���E�B���h�E
	m_veh_mes_win = CScene2D::Create(device, CImport::MAKE_UI_ASSY_OPTION, CScene2D::POINT_CENTER,2);
	m_veh_mes_win->SetSize(466.0f,91.0f);
	m_veh_mes_win->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55);

	// �����e�L�X�g
	m_cos_mes = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_5, CScene2D::POINT_CENTER);
	m_cos_mes->SetSize(466.0f,91.0f);
	m_cos_mes->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55 + 91.0f);
	// �����E�B���h�E
	m_cos_mes_win = CScene2D::Create(device, CImport::MAKE_UI_COS_OPTION, CScene2D::POINT_CENTER,2);
	m_cos_mes_win->SetSize(466.0f,91.0f);
	m_cos_mes_win->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55 + 91.0f);
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
			if(vehicle_id<=0)
			{
				vehicle_id=0;
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

//=============================================================================
// �A�j���[�V�����̍X�V
//=============================================================================
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
//=============================================================================
// �J�[�\���̍X�V
//=============================================================================
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

//=============================================================================
// �R�X�`���[���A�A�b�V�[�̍X�V
//=============================================================================
void CEquipmentChoice::cosUpdate(int id)
{
	switch (id)
	{
		CImport::TEXTURES texid,assid;
	case 0:
		texid=m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT,-1);
		assid=m_player->ConsultationVehicleTexID(-1);
		if(texid==CImport::TEX_MAX)
		{
			m_cos[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_cos[id]->SetColor(255,255,255,255);
		}

		if(assid==CImport::TEX_MAX)
		{
			m_ass[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_ass[id]->SetColor(255,255,255,255);
		}

		m_cos[id]->SetTex(texid);
		m_ass[id]->SetTex(assid);
		break;

	case 1:
		m_cos[id]->SetTex(m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT));
		m_ass[id]->SetTex(m_player->ConsultationVehicleTexID());
		break;

	case 2:
		texid=m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT,1);
		assid=m_player->ConsultationVehicleTexID(1);
		if(texid==CImport::TEX_MAX)
		{
			m_cos[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_cos[id]->SetColor(255,255,255,255);
		}

		if(assid==CImport::TEX_MAX)
		{
			m_ass[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_ass[id]->SetColor(255,255,255,255);
		}

		m_cos[id]->SetTex(texid);
		m_ass[id]->SetTex(assid);
		break;
	}
}