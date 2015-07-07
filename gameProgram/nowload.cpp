//*****************************************************************************
//
// CFade�N���X [fade.cpp]
// Author :MAI TANABE |KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "nowload.h"
#include "thr_obj.h"
#include "loading_icon.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ��錾(����)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
volatile bool CNLoad::m_EndThread;//(����)
const float CNLoad::UP_MAX = 10.0f;
const float CNLoad::DOWN_MAX = 0.0f;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾(����)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned __stdcall NowLoad( LPVOID Param );//(����)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNLoad::CNLoad()
{

}
//=============================================================================
// ����
//=============================================================================
CNLoad* CNLoad::Create( LPDIRECT3DDEVICE9 device )
{
	CNLoad* p = new CNLoad;
	p->m_now_load = p;
	p->Init( device );
	return p;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CNLoad::Init(LPDIRECT3DDEVICE9 device)
{
	m_device = device;
	m_LoadIcon = CLIcon::Create( device , CImport::PLAYER_DEFAULT_WAIT , CScene2D::POINT_CENTER , 4 , D3DXVECTOR2( SCREEN_WIDTH*0.5f , SCREEN_HEIGHT*0.5f ) );
	m_ThrHandle = (HANDLE)_beginthreadex( NULL , 0 , NowLoad , (void*)this , 0 , NULL );
	SetThreadPriority( m_ThrHandle , THREAD_PRIORITY_TIME_CRITICAL );

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CNLoad::Uninit(void)
{
	if( m_EndThread == false )
	{
		m_EndThread = true;//(����)
		WaitForSingleObject( m_ThrHandle , INFINITE );//(����)
	}
	delete this;
}
//=============================================================================
// �A�j���[�V����(�X���b�h:����)
//=============================================================================
unsigned __stdcall NowLoad( LPVOID Param )
{
	CNLoad* now_load = (CNLoad*)Param;
	while(1)
	{
		CLIcon* load_icon = now_load->GetLIcon();
		if( load_icon != NULL )
		{
			load_icon->Update();
			load_icon->Draw();
		}
		if( now_load->GetEndThread() == TRUE )
		{
			_endthread();
		}
	}
}