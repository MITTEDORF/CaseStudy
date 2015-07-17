//*****************************************************************************
//
// CGame�N���X [game.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "game.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

#include "result.h"
#include "gameclear.h"
#include "gameover.h"

#include "inputKeyboard.h"

//�v���C���[���䏈��
#include "character_player.h"
#include "particle_manager.h"

// �w�i
#include "sky.h"
#include "background_manager.h"

// ��Q���}�l�[�W��
#include "stum_manager.h"

// �n�ʃ}�l�[�W��
#include "road_manager.h"

// �^�[�Q�b�g�}�l�[�W��
#include "target_manager.h"

#include "configholder.h"

#include "stage_select_conf.h"
#include "listObject.h"

#include "character_goal.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ROAD_NUM	(SCREEN_WIDTH / ROAD_SIZE)
#define ROAD_POS	(SCREEN_HEIGHT - ROAD_SIZE)

#define SCREEN_HALF	(640)	// 1280 / 2

#define COUNTDOWN_DEFX (250.0f)
#define COUNTDOWN_DEFY (375.0f)
#define COUNTDOWN_DEFX2 (821.0f)
#define COUNTDOWN_DEFY2 (201.0f)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(LPDIRECT3DDEVICE9 device)
{
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
	m_sound->Play(CSound::SOUND_LABEL_GAMEBGM);

	// �X�e�[�^�X������
	m_sequence = 4;

	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGame::Uninit(void)
{
	//----------------------------
	// �w�i
	//----------------------------
	// ��
	SAFE_END(m_sky);

	SAFE_DELETE(m_bg);

	// ��Q��
	SAFE_DELETE(m_stumbler);
	// ���H
	SAFE_DELETE(m_road);
	// �^�[�Q�b�g
	SAFE_DELETE(m_target);

	// �V�[��
	CScene::ReleaseAll();

	//----------------------------
	// �T�E���h�̒�~
	//----------------------------
	m_sound->Stop(CSound::SOUND_LABEL_GAMEBGM);
}

//=============================================================================
// �X�V
//=============================================================================
void CGame::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//----------------------------
		// �f�o�b�O�R�}���h
		//----------------------------
		Debug();

		//----------------------------
		// �X�V���e
		//----------------------------
		switch(m_sequence)
		{
		case 0:
			CListObject::LinkDraw(m_countdown[0], 4);
			m_time++;
			m_countdown[0]->SetSize(COUNTDOWN_DEFX * (3.0f - (2.0f / 60.0f * m_time)), COUNTDOWN_DEFY * (3.0f - (2.0f / 60.0f * m_time)));
			m_countdown[0]->SetColor(1.0f, 1.0f, 1.0f, 1.0f - (0.6f / 60.0f * m_time));
			if(m_time >= 61)
			{
				m_time = 0;
				m_sequence = 1;
				m_countdown[0]->SetSize(COUNTDOWN_DEFX * 3, COUNTDOWN_DEFY * 3);
				m_countdown[0]->SetCord(0, D3DXVECTOR2((1.0f / 3.0f) * 1, 0.0f));
				m_countdown[0]->SetCord(1, D3DXVECTOR2((1.0f / 3.0f) * 2, 0.0f));
				m_countdown[0]->SetCord(2, D3DXVECTOR2((1.0f / 3.0f) * 1, 1.0f));
				m_countdown[0]->SetCord(3, D3DXVECTOR2((1.0f / 3.0f) * 2, 1.0f));
				m_countdown[0]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			break;
		case 1:
			m_time++;
			m_countdown[0]->SetSize(COUNTDOWN_DEFX * (3.0f - (2.0f / 60.0f * m_time)), COUNTDOWN_DEFY * (3.0f - (2.0f / 60.0f * m_time)));
			m_countdown[0]->SetColor(1.0f, 1.0f, 1.0f, 1.0f - (0.6f / 60.0f * m_time));
			if(m_time >= 61)
			{
				m_time = 0;
				m_sequence = 2;
				m_countdown[0]->SetSize(COUNTDOWN_DEFX * 3, COUNTDOWN_DEFY * 3);
				m_countdown[0]->SetCord(0, D3DXVECTOR2((1.0f / 3.0f) * 0, 0.0f));
				m_countdown[0]->SetCord(1, D3DXVECTOR2((1.0f / 3.0f) * 1, 0.0f));
				m_countdown[0]->SetCord(2, D3DXVECTOR2((1.0f / 3.0f) * 0, 1.0f));
				m_countdown[0]->SetCord(3, D3DXVECTOR2((1.0f / 3.0f) * 1, 1.0f));
				m_countdown[0]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			break;
		case 2:
			m_time++;
			m_countdown[0]->SetSize(COUNTDOWN_DEFX * (3.0f - (2.0f / 60.0f * m_time)), COUNTDOWN_DEFY * (3.0f - (2.0f / 60.0f * m_time)));
			m_countdown[0]->SetColor(1.0f, 1.0f, 1.0f, 1.0f - (0.6f / 60.0f * m_time));
			if(m_time >= 61)
			{
				m_time = 0;
				m_sequence = 3;
				CListObject::UnlinkDraw(m_countdown[0]);
				CListObject::LinkDraw(m_countdown[1], 4);
			}
			break;
		case 3:
			m_time++;
			m_countdown[1]->SetSize(COUNTDOWN_DEFX2 * (0.5f + (1.0f / 60.0f * m_time)), COUNTDOWN_DEFY2 * (0.5f + (1.0f / 60.0f * m_time)));
			m_countdown[1]->SetColor(1.0f, 1.0f, 1.0f, 0.6f + (0.4f / 60.0f * m_time));
			if(m_time >= 61)
			{
				m_time = 0;
				m_sequence = 4;
				CListObject::UnlinkDraw(m_countdown[1]);
				m_player->Set_isGame(true);
			}
			break;
		case 4:
			{
				// �^�C�}�[�X�V
				m_time++;

				m_timePol[0]->SetCord(0, D3DXVECTOR2( ((m_time/36000) % 6) * 0.1f,			0.0f));
				m_timePol[0]->SetCord(1, D3DXVECTOR2( ((m_time/36000) % 6) * 0.1f + 0.1f,	0.0f));
				m_timePol[0]->SetCord(2, D3DXVECTOR2( ((m_time/36000) % 6) * 0.1f,			1.0f));
				m_timePol[0]->SetCord(3, D3DXVECTOR2( ((m_time/36000) % 6) * 0.1f + 0.1f,	1.0f));

				m_timePol[1]->SetCord(0, D3DXVECTOR2( ((m_time/3600) % 10) * 0.1f,			0.0f));
				m_timePol[1]->SetCord(1, D3DXVECTOR2( ((m_time/3600) % 10) * 0.1f + 0.1f,	0.0f));
				m_timePol[1]->SetCord(2, D3DXVECTOR2( ((m_time/3600) % 10) * 0.1f,			1.0f));
				m_timePol[1]->SetCord(3, D3DXVECTOR2( ((m_time/3600) % 10) * 0.1f + 0.1f,	1.0f));

				m_timePol[3]->SetCord(0, D3DXVECTOR2( ((m_time/600) % 6) * 0.1f,			0.0f));
				m_timePol[3]->SetCord(1, D3DXVECTOR2( ((m_time/600) % 6) * 0.1f + 0.1f,		0.0f));
				m_timePol[3]->SetCord(2, D3DXVECTOR2( ((m_time/600) % 6) * 0.1f,			1.0f));
				m_timePol[3]->SetCord(3, D3DXVECTOR2( ((m_time/600) % 6) * 0.1f + 0.1f,		1.0f));

				m_timePol[4]->SetCord(0, D3DXVECTOR2( ((m_time/60) % 10) * 0.1f,			0.0f));
				m_timePol[4]->SetCord(1, D3DXVECTOR2( ((m_time/60) % 10) * 0.1f + 0.1f,		0.0f));
				m_timePol[4]->SetCord(2, D3DXVECTOR2( ((m_time/60) % 10) * 0.1f,			1.0f));
				m_timePol[4]->SetCord(3, D3DXVECTOR2( ((m_time/60) % 10) * 0.1f + 0.1f,		1.0f));

				// ��̍X�V�i�X�N���[���j
				m_sky->Update();

				// �v���C���[�̍��W�擾
				D3DXVECTOR2 playerPos = m_player->GetPos();

				m_stumbler->UnLinkStum();

				// �X�N���[������(�v���C���[����ʔ������z������)
				if(playerPos.x >= SCREEN_HALF)
				{
					float scroll = playerPos.x - SCREEN_HALF;

					// �v���C���[�͉�ʐ^�񒆂�
					m_player->SetPosX(SCREEN_HALF);

					// ��̃X�N���[��
					m_sky->Scroll(scroll * 0.01f);

					// �w�i�̃X�N���[��
					m_bg->Scroll(scroll);

					//�p�[�e�B�N���̃X�N���[��
					m_player->ParticleScrol(scroll);

					// ��Q���̃X�N���[��
					m_stumbler->Scroll(scroll);
					m_target->Scroll(scroll);

					// ���H�̃X�N���[��
					m_road->Scroll(scroll);
				}
			}
			break;
		default:
			break;
		}
	}

	//�S�����蔻��
	ColAll();

	//----------------------------
	// ��ʑJ��
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		if(m_player->isDeth_())
		{
			CManager::SetNextPhase((CPhase*)new CGameOver());
		}

		else
		{
			CManager::SetNextPhase((CPhase*)new CGameClear(m_time, m_player->HP_()));
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �f�o�b�N���e
//=============================================================================
void CGame::Debug(void)
{
	//----------------------------
	// ��ʑJ��
	//----------------------------
	/*if(m_keyboard->GetTrigger(DIK_RETURN))
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}*/
}

//=============================================================================
// �I�u�W�F�N�g������
//=============================================================================
void CGame::InitObject(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// �w�i
	//----------------------------
	    CImport::MAPS map;
    switch (CConfigHolder::Get(CONFIG_STAGE))
    {
    case STAGE_DESERT:
        map=CImport::STAGE_DESERT;
        break;
    case STAGE_WATERSIDE:
        map=CImport::STAGE_WATERSIDE;
        break;
    case STAGE_GLACIER:
        map=CImport::STAGE_GLACIER;
        break;
    case STAGE_SAVANNAH:
        map=CImport::STAGE_SAVANNAH;
        break;
    case STAGE_FOREST:
        map=CImport::STAGE_FOREST;
        break;
    }


	// ��
	m_sky = CSky::Create(device);
	// �w�i
	m_bg = CBackgroundManager::Create(device,map);
	// ���H
	m_road = CRoadManager::Create(device,map);
	// ��Q��
	m_stumbler = CStumManager::Create(device,map);
	m_target = CTargetManager::Create(device,map);

	m_target->GoalTexSet(CImport::TARGET_OFF);

	m_char_goal=NULL;

	// �t�B���^�[
	CScene2D* filter = CScene2D::Create(device, CImport::NONE, CScene2D::POINT_LEFTTOP, 2);
	filter->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	filter->SetColor(1.0f, 1.0f, 1.0f, 0.1f);

	
	m_char_goal=CCharacterGoal::Create(m_device);

	//----------------------------
	// �L�����N�^�[
	//----------------------------
	//�ݒ���Ǘ��N���X����R�X�`���[�����Ə�蕨���擾
	int local_costume_id=CConfigHolder::Get(CONFIG_COSTUME);
	int local_vehicle_id=CConfigHolder::Get(CONFIG_ASSY);

	//�v���C���[�̐���
	m_player=CPlayer::Create(device,(CostumeID)local_costume_id,(VehicleID)local_vehicle_id);
	m_player->SetPos(120.0f, SCREEN_HEIGHT - 128.0f);
	m_player->SetHitSize(D3DXVECTOR2(108.0f, 90.0f));
	m_player->SetHitOffset(D3DXVECTOR2(0.0f, 0.0f));
	m_player->SetKeyboard(m_keyboard);
	m_player->SetPadX(m_padX);
	//m_player->Set_isGame(false);
	// �^�C�}�[
	m_time = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(SCREEN_WIDTH * 0.78f, SCREEN_HEIGHT * 0.01f);
	for(int i = 0; i < 5; i++)
	{
		m_timePol[i] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);

		if(i != 2)
		{
			m_timePol[i]->SetSize(60.0f, 100.0f);
		}
		else
		{
			m_timePol[i]->SetSize(30.0f, 100.0f);
		}
		
		if(i >2)
		{
			m_timePol[i]->SetPos(pos.x + 60.0f * i - 30.0f, pos.y);
		}
		else
		{
			m_timePol[i]->SetPos(pos.x + 60.0f * i, pos.y);
		}

		if(i != 2)
		{
			m_timePol[i]->SetTex(CImport::NUMBER);
			m_timePol[i]->SetCord(0, D3DXVECTOR2(0.0f, 0.0f));
			m_timePol[i]->SetCord(1, D3DXVECTOR2(0.1f, 0.0f));
			m_timePol[i]->SetCord(2, D3DXVECTOR2(0.0f, 1.0f));
			m_timePol[i]->SetCord(3, D3DXVECTOR2(0.1f, 1.0f));
		}
		else
		{
			m_timePol[i]->SetTex(CImport::COLON_HALF);
		}
	}

	// �J�E���g�_�E���p
	m_countdown[0] = CScene2D::Create(device, CImport::COUNTDOWN_NUM, CScene2D::POINT_CENTER);
	m_countdown[0]->SetSize(COUNTDOWN_DEFX * 3, COUNTDOWN_DEFY * 3);
	m_countdown[0]->SetPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_countdown[0]->SetCord(0, D3DXVECTOR2((1.0f / 3.0f) * 2, 0.0f));
	m_countdown[0]->SetCord(1, D3DXVECTOR2((1.0f / 3.0f) * 3, 0.0f));
	m_countdown[0]->SetCord(2, D3DXVECTOR2((1.0f / 3.0f) * 2, 1.0f));
	m_countdown[0]->SetCord(3, D3DXVECTOR2((1.0f / 3.0f) * 3, 1.0f));
	CListObject::UnlinkDraw(m_countdown[0]);

	m_countdown[1] = CScene2D::Create(device, CImport::START, CScene2D::POINT_CENTER);
	m_countdown[1]->SetSize(COUNTDOWN_DEFX2 * 0.5f, COUNTDOWN_DEFY2 * 0.5f);
	m_countdown[1]->SetPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_countdown[1]->SetColor(1.0f, 1.0f, 1.0f, 0.6f);
	CListObject::UnlinkDraw(m_countdown[1]);
}

//=============================================================================
// �S�����蔻��
//=============================================================================
void CGame::ColAll()
{
	// �S�[���ƐڐG����
	if( m_target->CheckHitGoal( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
	{
		m_player->PlayerGoal();
	}

	//�v���C���Ə�Q���̓����蔻��
	if(m_stumbler->CheckHit( m_player->GetHitPos() , m_player->GetHitSize() , CScene2D::POINT_CENTER ))
	{
		m_player->AddHP(-1);
	}

	//���C�g�j���O����
	if(m_player->isLitninng()&&!m_char_goal->isStart_())
	{
		m_player->PaticleStart((CScene*)m_target->Goal_());
	}

	if(!m_player->isDeth_())
	{
		ColPlayer();
	}

	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//�v���C��������ł�ꍇ�t�F�[�h�J�n
		if(m_player->isDeth_())
		{
			m_player->PlayerReflash(false);
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}

		if(m_player->isFadeStart_())
		{
			m_target->GoalTexSet(CImport::TARGET_ON);
			m_char_goal->Start((CScene*)m_target->Goal_());
		}

		if(m_char_goal->isFade_())
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}
}

void CGame::ColPlayer()
{
	// �v���C���[�Ɠ��H�̓����蔻��A�����߂�
	D3DXVECTOR2 tmp[2],newpos;

	//�S���H�Ƃ̓����蔻����s��(tmp[0]=�����߂���,tmp[1]=���@���W)
	tmp[0] = m_road->CheckHit( m_player->GetHitPos() + D3DXVECTOR2(0.0f, 19.0f) , m_player->GetHitSize() , CScene2D::POINT_CENTER );
	tmp[1] = m_player->GetPos();

	//Y�����߂��K�p���Ȃ�
	newpos.x= tmp[0].x + tmp[1].x;
	newpos.y= tmp[0].y + tmp[1].y;

	//���H�̏ォ�瓖�������ꍇ
	if(tmp[0].y<0)
	{
		if(!m_player->isGround_())
		{
			newpos.x= tmp[1].x;
			m_player->isGround_set(true);
		}
		//Y�̑��x��0�ɂ��ďd�͂�؂�
		m_player->SetCanJump();
		m_player->SpdKill();
	}

	else
	{
		m_player->isGround_set(false);
	}

	//���H�̉����瓖�������ꍇ
	if(tmp[0].y>0)
	{
		m_player->SpdKill();
	}

	//���@�̍��W�ɓK�p
	m_player->SetPos(newpos);
}
