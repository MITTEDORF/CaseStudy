//*****************************************************************************
//
// CManeger�N���X [manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "manager.h"

#include "renderer.h"
#include "debugproc.h"
#include "import.h"
#include "sound.h"

#include "phase.h"
#include "title.h"
#include "game.h"
#include "result.h"

#include "inputKeyboard.h"
#include "inputPadX.h"

#include "listObject.h"
#include "scene2D.h"

#include "Thread.h"
#include "nowload.h"

#include "configholder.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CPhase* CManager::m_phaseNext = NULL;
CPhase* CManager::m_phase = NULL;
CNLoad* CManager::m_now_load=NULL;
HWND	CManager::m_window_handle = NULL;
CThread* CManager::m_Thread = NULL;
CRenderer* CManager::m_renderer;
bool CManager::m_loading_flag;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager(void)
{

}

//=============================================================================
// ����
//=============================================================================
CManager* CManager::Create(HINSTANCE instance, HWND wnd, bool window)
{
	CManager* pointer = new CManager;
	pointer->Init(instance, wnd, window);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HINSTANCE instance, HWND wnd, bool window)
{
	LPDIRECT3DDEVICE9 device;

	//----------------------------
	// ���ʕ�
	//----------------------------
	// �E�B���h�E�n���h��
	m_window_handle = wnd;
	// �����_���[
	m_renderer	= CRenderer::Create(wnd, window);
	device		= m_renderer->GetDevice();

	// ����
	m_keyboard = CInputKeyboard::Create(instance, wnd);
	m_padX = CInputPadX::Create();

	// �f�o�b�O�\��
	m_debugproc = CDebugproc::Create(device);
	m_renderer->SetDebugproc(m_debugproc);

	//�ݒ���Ǘ�
	m_configholder = new CConfigHolder();

	//----------------------------
	// ���[�h���`��
	//----------------------------
	m_loading_flag = true;
	m_now_load = new CNLoad;
	m_now_load->Init(device);

	m_Thread = new CThread();
	m_Thread->Create( InitLoad );

	//----------------------------
	// �t�@�C���ǂݍ���
	//----------------------------
	m_import = CImport::Create(device);
	m_sound  = CSound::Create(wnd);

	//----------------------------
	// ���[�h�I��
	//----------------------------
	m_loading_flag = false;
	// �X���b�h�������Ă�����j��
	if (m_Thread)
	{
		m_Thread->Release();
		delete m_Thread;
		m_Thread = NULL;
	}

	//----------------------------
	// �t�F�[�Y
	//----------------------------
	m_phaseNext = (CPhase*)new CTitle;
	Change();
	m_phase->SetKeyboard(m_keyboard);
	m_phase->SetPadX(m_padX);
	m_phase->SetSound(m_sound);
	m_phase->Init(device);

	m_phaseNext = m_phase;

	//----------------------------
	// ���͐ݒ�
	//----------------------------
	m_debugproc->SetKeyboard(m_keyboard);

	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CManager::Uninit(void)
{
	//----------------------------
	// �t�F�[�Y
	//----------------------------
	SAFE_END(m_phase);

	//----------------------------
	// ���ʕ�
	//----------------------------
	// �T�E���h
	SAFE_END(m_sound);

	// �C���|�[�g
	SAFE_END(m_import);

	// �f�o�b�O�\��
	SAFE_END(m_debugproc);

	// ����
	SAFE_END(m_keyboard);
	SAFE_END(m_padX);

	// �����_���[
	SAFE_END(m_renderer);

	//�ݒ���Ǘ�
	SAFE_DELETE(m_configholder);

	// ����Y������Ȃ���
	CScene::ReleaseAll();

	//�i�E���[�f�B���O
	m_now_load->Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CManager::Update(void)
{
	//----------------------------
	// ���ʕ�(�����_���[�A�T�E���h�ȊO)
	//----------------------------
	// �f�o�b�O�\��
	m_debugproc->Update();

	if(CDebugproc::GetDrawFrag())
	{
		// FPS�X�V
		m_debugproc->PrintDebugProc("FPS:%d\n", m_renderer->GetFPS());
	}

	// ����
	m_keyboard->Update();
	m_padX->Update();

	//----------------------------
	// �t�F�[�Y
	//----------------------------
	if( m_loading_flag == false )
	{
		// �X���b�h�������Ă�����j��
		if (m_Thread)
		{
			m_Thread->Release();
			delete m_Thread;
			m_Thread = NULL;
		}

		if(m_phase != NULL)
		{
			m_phase->Update();
			// �����_���[
			m_renderer->Update();
		}
	}
	else
	{
		m_now_load->Update();
	}

	//----------------------------
	// �T�E���h
	//----------------------------

	//----------------------------
	// �t�F�[�Y�ؑ�
	//----------------------------
	if(m_phaseNext != m_phase)
	{
		Change();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CManager::Draw(void)
{
	if( m_loading_flag == false )
	{
		//----------------------------
		// �t�F�[�Y
		//----------------------------
		if(m_phase != NULL)
		{
			m_phase->Draw();
			//----------------------------
			// �����_���[
			//----------------------------
			m_renderer->Draw();
		}

	}
	else
	{
		m_now_load->Draw();
	}
}

//=============================================================================
// FPS����
//=============================================================================
void CManager::CalculateFPS(DWORD frameCnt, DWORD curTime, DWORD FPSLastTime)
{
	m_renderer->SetFPS(frameCnt * 1000 / (curTime - FPSLastTime));
}
//=============================================================================
// �t�F�[�Y�ύX
//=============================================================================
void CManager::Change( void )
{
	// ���݃t�F�[�Y��j��
	SAFE_END(m_phase);
	// ���̃t�F�[�Y�𐶐��E������
	m_phase = m_phaseNext;

	m_loading_flag = true;
	m_Thread = new CThread();
	m_Thread->Create( Load );
}
//=============================================================================
// ���[�h
//=============================================================================
void CManager::Load( void )
{
	m_phase->Init(m_renderer->GetDevice());
	m_loading_flag = false;
}
//=============================================================================
// ���񃍁[�h
//=============================================================================
void CManager::InitLoad( void )
{
	DWORD execLastTime;	// ��������
	DWORD curTime;		// ���ݎ���
	// �t���[���J�E���g
	timeBeginPeriod(1);				// ����\��ݒ�
	execLastTime = timeGetTime();
	curTime	 = 0;					// ���ݎ����ƃJ�E���g�̏�����

	while(m_loading_flag)
	{
		curTime = timeGetTime();	// �V�X�e���������擾
		if((curTime - execLastTime) >= (1000 / 60))
		{
			execLastTime = curTime;	// ��������������ۑ�

			if( m_now_load != NULL )
			{
				m_now_load->Update();
				m_now_load->Draw();
			}
		}
	}
	// �t���[���J�E���g
	timeEndPeriod(1);	// ����\��߂�

}