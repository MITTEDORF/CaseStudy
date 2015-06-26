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

#include "result.h"
#include "gameclear.h"
#include "gameover.h"

#include "inputKeyboard.h"

//�v���C���[���䏈��
#include "character_player.h"
#include "particle_manager.h"

// �w�i
#include "sky.h"
#include "background.h"

#include "goal.h"

// ��Q���}�l�[�W��
#include "stum_manager.h"

// �n�ʃ}�l�[�W��
#include "road_manager.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ROAD_NUM	(SCREEN_WIDTH / ROAD_SIZE)
#define ROAD_POS	(SCREEN_HEIGHT - ROAD_SIZE)

#define SCREEN_HALF	(640)	// 1280 / 2

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------
// ��Q���֘A�i��ŏ����Ă�
CStumManager* g_stumbler;
//----------------------------------------
// ���H�֘A�i��ŏ����Ă�
CRoadManager* g_road;

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
void CGame::Uninit(void)
{
	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------
	// ��
	SAFE_END(m_sky);

	SAFE_END(m_bg);

	//----------------------------------------
	// ��Q���֘A�i��ŏ����Ă�
	SAFE_DELETE(g_stumbler);
	//----------------------------------------
	// ���H�֘A�i��ŏ����Ă�
	SAFE_DELETE(g_road);

	// �V�[��
	CScene::ReleaseAll();
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
		// ��̍X�V�i�X�N���[���j
		m_sky->Update();

		// �v���C���[�̍��W�擾
		D3DXVECTOR2 playerPos = m_player->GetPos();

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

			//----------------------------------------
			// ��Q���֘A�i��ŏ����Ă�
			g_stumbler->Scroll(scroll);
			//g_road->Scroll(scroll);

			//�S�[���̃X�N���[��(���� 6/2_12�����ǉ�)
			m_Goal->Scroll( scroll );
		}
		else if(playerPos.x < 0)
		{
			float scroll = 0 - playerPos.x;

			// �v���C���[�͉�ʍ��[��
			m_player->SetPosX(0);

			// ��̃X�N���[��
			m_sky->Scroll(scroll * 0.01f);

			// �w�i�̃X�N���[��
			m_bg->Scroll(scroll);

			//�p�[�e�B�N���̃X�N���[��
			m_player->ParticleScrol(scroll);

			//----------------------------------------
			// ��Q���֘A�i��ŏ����Ă�
			g_stumbler->Scroll(scroll);
			//g_road->Scroll(scroll);
		}

		//�S�����蔻��
		ColAll();

		//�����u��
		if( m_Goal->CheckCollisionAABB( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
			m_player->PlayerReflash();
		}
	}

	//----------------------------
	// ��ʑJ��
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		if(m_player->isDeth_())
		{
			CManager::SetNextPhase((CPhase*)new CGameOver);
		}

		else
		{
			CManager::SetNextPhase((CPhase*)new CGameClear);
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
	if(m_keyboard->GetTrigger(DIK_RETURN))
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}

//=============================================================================
// �I�u�W�F�N�g������
//=============================================================================
void CGame::InitObject(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// �w�i
	//----------------------------
	// ��
	m_sky = CSky::Create(device);

	// �w�i
	m_bg = CBackground::Create(device, CBackground::FOREST);

	//-----------------------------
	// ���H�֘A(��ŏC�����Ă�
	g_road = CRoadManager::Create(device);
	//-----------------------------
	// ��Q���֘A(��ŏC�����Ă�
	g_stumbler = CStumManager::Create(device);

	//----------------------------
	// �L�����N�^�[
	//----------------------------
	//�v���C���[�̐���
	m_player=CPlayer::Create(device,costume_id,vehicle_id);
	m_player->SetPos(120.0f,300.0f);
	m_player->SetKeyboard(m_keyboard);


	//goal(���� 6/9_AM_10�����ύX)
	m_Goal = m_Goal->Create( device , CImport::GOAL_ON , CScene2D::POINT_LEFTTOP , 2 , D3DXVECTOR2( 8500.0f , SCREEN_HEIGHT - ((1 * 64) + 128) ) );
}

//=============================================================================
// �S�����蔻��
//=============================================================================
void CGame::ColAll()
{
	//�v���C���Ə�Q���̓����蔻��
	if(g_stumbler->CheckHit( m_player->GetHitPos() , m_player->GetHitSize() , CScene2D::POINT_CENTER ))
	{
		m_player->AddHP(-1);
	}

	// �v���C���[�Ɠ��H�̓����蔻��A�����߂�
	D3DXVECTOR2 tmp[2];
	tmp[0] = g_road->CheckHit( m_player->GetHitPos() , m_player->GetHitSize() , CScene2D::POINT_CENTER );
	tmp[1] = m_player->GetPos();
	m_player->SetPos(tmp[0].x + tmp[1].x, tmp[0].y + tmp[1].y);

	//���C�g�j���O����
	if(m_player->isLitninng())
	{
		if((m_Goal->CheckCollisionAABB(m_player->GetPos() , m_player->GetSize()*3.0f , CScene2D::POINT_CENTER )))
		{
			m_player->PaticleStart(m_Goal);
		}

		else
		{
			m_player->PaticleStart(NULL);
		}
	}

	//�v���C��������ł�ꍇ�t�F�[�h�J�n
	if(m_player->isDeth_())
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}

