//*****************************************************************************
//
// CGameクラス [game.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "game.h"
#include "manager.h"
#include "fade.h"

#include "result.h"

#include "inputKeyboard.h"

//プレイヤー制御処理
#include "character_player.h"

// 背景
#include "sky.h"
#include "background.h"

#include "goal.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ROAD_SIZE	(32.0f)
#define ROAD_NUM	(40.0f)		// 1280 / 32
#define ROAD_POS	(688)		// 720 - 32

#define SCREEN_HALF	(640)	// 1280 / 2

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGame::Init(LPDIRECT3DDEVICE9 device)
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
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGame::Uninit(void)
{
	//----------------------------
	// オブジェクト
	//----------------------------
	// 空
	SAFE_END(m_sky);

	SAFE_END(m_bg);

	// シーン
	CScene::ReleaseAll();
}

//=============================================================================
// 更新
//=============================================================================
void CGame::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//----------------------------
		// デバッグコマンド
		//----------------------------
		Debug();

		//----------------------------
		// 更新内容
		//----------------------------
		// 空の更新（スクロール）
		m_sky->Update();

		// プレイヤーの座標取得
		D3DXVECTOR2 playerPos = m_player->GetPos();

		// スクロール処理(プレイヤーが画面半分を越えた時)
		if(playerPos.x >= SCREEN_HALF)
		{
			float scroll = playerPos.x - SCREEN_HALF;

			// プレイヤーは画面真ん中に
			m_player->SetPosX(SCREEN_HALF);

			// 空のスクロール
			m_sky->Scroll(scroll * 0.01f);

			// 背景のスクロール
			m_bg->Scroll(scroll);
		}
		else if(playerPos.x < 0)
		{
			float scroll = 0 - playerPos.x;

			// プレイヤーは画面左端に
			m_player->SetPosX(0);

			// 空のスクロール
			m_sky->Scroll(scroll * 0.01f);

			// 背景のスクロール
			m_bg->Scroll(scroll);
		}
	}

	//----------------------------
	// 画面遷移
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		CManager::SetNextPhase((CPhase*)new CResult);
	}
}

//=============================================================================
// 描画
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// デバック内容
//=============================================================================
void CGame::Debug(void)
{
	//----------------------------
	// 画面遷移
	//----------------------------
	if(m_keyboard->GetTrigger(DIK_RETURN))
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CGame::InitObject(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// 背景
	//----------------------------
	// 空
	m_sky = CSky::Create(device);

	// 背景
	m_bg = CBackground::Create(device, CBackground::TWON);

	//----------------------------
	// 道
	//----------------------------
	CScene2D* road;
	for(int cnt = 0; cnt < ROAD_NUM; ++cnt)
	{
		road = CScene2D::Create(device, CImport::TEX_ASPHALT, CScene2D::POINT_LEFTTOP);
		road->SetSize(ROAD_SIZE, ROAD_SIZE);
		road->SetPos(ROAD_SIZE * cnt, ROAD_POS);
	}

	//----------------------------
	// キャラクター
	//----------------------------
	//プレイヤーの生成
	m_player=CPlayer::Create(device);
	m_player->SetPos(120.0f,300.0f);
	m_player->SetKeyboard(m_keyboard);

	//goal
	CGoal::Create( device , "data/TEXTURE/blockWall.png" , CScene2D::POINT_CENTER , 0 , D3DXVECTOR2( 120.0f , 300.0f ) );
}
