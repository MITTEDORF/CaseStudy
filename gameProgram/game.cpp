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
#include "gameclear.h"
#include "gameover.h"

#include "inputKeyboard.h"

//プレイヤー制御処理
#include "character_player.h"
#include "particle_manager.h"

// 背景
#include "sky.h"
#include "background.h"

#include "goal.h"

#include "stum_manager.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ROAD_SIZE	(64.0f)
#define ROAD_NUM	(SCREEN_WIDTH / ROAD_SIZE)
#define ROAD_POS	(SCREEN_HEIGHT - ROAD_SIZE)

#define SCREEN_HALF	(640)	// 1280 / 2

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------
// 障害物関連（後で消してね
CStumManager* g_stumbler;

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
	// バージョン表示
	//----------------------------
	m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);

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

			//----------------------------------------
			// 障害物関連（後で消してね
			g_stumbler->Scroll(scroll);

			//ゴールのスクロール(大井川 6/2_12時頃追加)
			m_Goal->Scroll( scroll );
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

			//----------------------------------------
			// 障害物関連（後で消してね
			g_stumbler->Scroll(scroll);
		}

		//全当たり判定
		ColAll();

		//α仮置き
		if( m_Goal->CheckCollisionAABB( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

	//----------------------------
	// 画面遷移
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
	m_bg = CBackground::Create(device, CBackground::FOREST);

	//----------------------------
	// 道
	//----------------------------
	CScene2D* road;
	for(int cnt = 0; cnt < ROAD_NUM; ++cnt)
	{
		road = CScene2D::Create(device, CImport::DIRT, CScene2D::POINT_LEFTTOP);
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

	g_stumbler = CStumManager::Create(device);

	//goal(大井川 6/9_AM_10時頃変更)
	m_Goal = m_Goal->Create( device , CImport::GOAL_ON , CScene2D::POINT_CENTER , 2 , D3DXVECTOR2( 1000.0f , 500.0f ) );
}

//=============================================================================
// 全当たり判定
//=============================================================================
void CGame::ColAll()
{
	//プレイヤと障害物の当たり判定
	if(g_stumbler->CheckHit( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ))
	{
		m_player->AddHP(-1);
	}

	//プレイヤが死んでる場合フェード開始
	if(m_player->isDeth_())
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}

