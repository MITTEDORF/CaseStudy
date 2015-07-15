//*****************************************************************************
//
// CManegerクラス [manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
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
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CPhase* CManager::m_phaseNext = NULL;
CPhase* CManager::m_phase = NULL;
CNLoad* CManager::m_now_load=NULL;
HWND	CManager::m_window_handle = NULL;
CThread* CManager::m_Thread = NULL;
CRenderer* CManager::m_renderer;
bool CManager::m_loading_flag;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CManager* CManager::Create(HINSTANCE instance, HWND wnd, bool window)
{
	CManager* pointer = new CManager;
	pointer->Init(instance, wnd, window);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManager::Init(HINSTANCE instance, HWND wnd, bool window)
{
	LPDIRECT3DDEVICE9 device;

	//----------------------------
	// 共通部
	//----------------------------
	// ウィンドウハンドル
	m_window_handle = wnd;
	// レンダラー
	m_renderer	= CRenderer::Create(wnd, window);
	device		= m_renderer->GetDevice();

	// 入力
	m_keyboard = CInputKeyboard::Create(instance, wnd);
	m_padX = CInputPadX::Create();

	// デバッグ表示
	m_debugproc = CDebugproc::Create(device);
	m_renderer->SetDebugproc(m_debugproc);

	//設定情報管理
	m_configholder = new CConfigHolder();

	//----------------------------
	// ロード中描画
	//----------------------------
	m_loading_flag = true;
	m_now_load = new CNLoad;
	m_now_load->Init(device);

	m_Thread = new CThread();
	m_Thread->Create( InitLoad );

	//----------------------------
	// ファイル読み込み
	//----------------------------
	m_import = CImport::Create(device);
	m_sound  = CSound::Create(wnd);

	//----------------------------
	// ロード終了
	//----------------------------
	m_loading_flag = false;
	// スレッドが生きていたら破棄
	if (m_Thread)
	{
		m_Thread->Release();
		delete m_Thread;
		m_Thread = NULL;
	}

	//----------------------------
	// フェーズ
	//----------------------------
	m_phaseNext = (CPhase*)new CTitle;
	Change();
	m_phase->SetKeyboard(m_keyboard);
	m_phase->SetPadX(m_padX);
	m_phase->SetSound(m_sound);
	m_phase->Init(device);

	m_phaseNext = m_phase;

	//----------------------------
	// 入力設定
	//----------------------------
	m_debugproc->SetKeyboard(m_keyboard);

	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManager::Uninit(void)
{
	//----------------------------
	// フェーズ
	//----------------------------
	SAFE_END(m_phase);

	//----------------------------
	// 共通部
	//----------------------------
	// サウンド
	SAFE_END(m_sound);

	// インポート
	SAFE_END(m_import);

	// デバッグ表示
	SAFE_END(m_debugproc);

	// 入力
	SAFE_END(m_keyboard);
	SAFE_END(m_padX);

	// レンダラー
	SAFE_END(m_renderer);

	//設定情報管理
	SAFE_DELETE(m_configholder);

	// 解放忘れをしない為
	CScene::ReleaseAll();

	//ナウローディング
	m_now_load->Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CManager::Update(void)
{
	//----------------------------
	// 共通部(レンダラー、サウンド以外)
	//----------------------------
	// デバッグ表示
	m_debugproc->Update();

	if(CDebugproc::GetDrawFrag())
	{
		// FPS更新
		m_debugproc->PrintDebugProc("FPS:%d\n", m_renderer->GetFPS());
	}

	// 入力
	m_keyboard->Update();
	m_padX->Update();

	//----------------------------
	// フェーズ
	//----------------------------
	if( m_loading_flag == false )
	{
		// スレッドが生きていたら破棄
		if (m_Thread)
		{
			m_Thread->Release();
			delete m_Thread;
			m_Thread = NULL;
		}

		if(m_phase != NULL)
		{
			m_phase->Update();
			// レンダラー
			m_renderer->Update();
		}
	}
	else
	{
		m_now_load->Update();
	}

	//----------------------------
	// サウンド
	//----------------------------

	//----------------------------
	// フェーズ切替
	//----------------------------
	if(m_phaseNext != m_phase)
	{
		Change();
	}
}

//=============================================================================
// 描画
//=============================================================================
void CManager::Draw(void)
{
	if( m_loading_flag == false )
	{
		//----------------------------
		// フェーズ
		//----------------------------
		if(m_phase != NULL)
		{
			m_phase->Draw();
			//----------------------------
			// レンダラー
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
// FPS測定
//=============================================================================
void CManager::CalculateFPS(DWORD frameCnt, DWORD curTime, DWORD FPSLastTime)
{
	m_renderer->SetFPS(frameCnt * 1000 / (curTime - FPSLastTime));
}
//=============================================================================
// フェーズ変更
//=============================================================================
void CManager::Change( void )
{
	// 現在フェーズを破棄
	SAFE_END(m_phase);
	// 次のフェーズを生成・初期化
	m_phase = m_phaseNext;

	m_loading_flag = true;
	m_Thread = new CThread();
	m_Thread->Create( Load );
}
//=============================================================================
// ロード
//=============================================================================
void CManager::Load( void )
{
	m_phase->Init(m_renderer->GetDevice());
	m_loading_flag = false;
}
//=============================================================================
// 初回ロード
//=============================================================================
void CManager::InitLoad( void )
{
	DWORD execLastTime;	// 処理時刻
	DWORD curTime;		// 現在時刻
	// フレームカウント
	timeBeginPeriod(1);				// 分解能を設定
	execLastTime = timeGetTime();
	curTime	 = 0;					// 現在時刻とカウントの初期化

	while(m_loading_flag)
	{
		curTime = timeGetTime();	// システム時刻を取得
		if((curTime - execLastTime) >= (1000 / 60))
		{
			execLastTime = curTime;	// 処理した時刻を保存

			if( m_now_load != NULL )
			{
				m_now_load->Update();
				m_now_load->Draw();
			}
		}
	}
	// フレームカウント
	timeEndPeriod(1);	// 分解能を戻す

}