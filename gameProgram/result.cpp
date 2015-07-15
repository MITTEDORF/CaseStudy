//*****************************************************************************
//
// CResultクラス [result.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "result.h"
#include "manager.h"
#include "fade.h"

#include "title.h"

#include "inputKeyboard.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// 初期化
//=============================================================================
HRESULT CResult::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// デバイス取得
	//----------------------------
	m_device = device;

	//----------------------------
	// オブジェクト
	//----------------------------
	InitObject(device);

	//----------------------------
	// フェード
	//----------------------------
	m_fade = CFade::Create(device);
	m_fade->Start(CFade::FADESTATE_IN, 1, 1.0f, 1.0f, 1.0f, 1.0f);

	//----------------------------
	// バージョン表示
	//----------------------------
	/*m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);*/

	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CResult::Uninit(void)
{
	//----------------------------
	// オブジェクト
	//----------------------------
	// シーン
	CScene::ReleaseAll();
}

//=============================================================================
// 更新
//=============================================================================
void CResult::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//----------------------------
		// 入力
		//----------------------------
		if(m_keyboard->GetTrigger(DIK_RETURN))
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

	//----------------------------
	// 画面遷移
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		CManager::SetNextPhase((CPhase*)new CTitle);
	}
}

//=============================================================================
// 描画
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CResult::InitObject(LPDIRECT3DDEVICE9 device)
{
	//ロゴ

	//クリア画面
	if(isWin)
	{
		CScene2D* resultLogo = CScene2D::Create(device, CImport::PLAYER_GOODMOOD, CScene2D::POINT_CENTER);
		resultLogo->SetSize(1204.0f/2, 1329.0f/2);
		resultLogo->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	}

	//ゲームオーバー画面
	else
	{
		CScene2D* resultLogo = CScene2D::Create(device, CImport::PLAYER_BADMOOD, CScene2D::POINT_CENTER);
		resultLogo->SetSize(743.0f, 1274.0f);
		resultLogo->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	}
}