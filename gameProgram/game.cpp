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
#include "sound.h"

#include "result.h"
#include "gameclear.h"
#include "gameover.h"

#include "inputKeyboard.h"

//プレイヤー制御処理
#include "character_player.h"
#include "particle_manager.h"

// 背景
#include "sky.h"
#include "background_manager.h"

// 障害物マネージャ
#include "stum_manager.h"

// 地面マネージャ
#include "road_manager.h"

// ターゲットマネージャ
#include "target_manager.h"

#include "configholder.h"

#include "stage_select_conf.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ROAD_NUM	(SCREEN_WIDTH / ROAD_SIZE)
#define ROAD_POS	(SCREEN_HEIGHT - ROAD_SIZE)

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
	// バージョン表示
	//----------------------------
	/*m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);*/

	//----------------------------
	// サウンドの再生
	//----------------------------
	m_sound->Play(CSound::SOUND_LABEL_GAMEBGM);

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
	// 背景
	//----------------------------
	// 空
	SAFE_END(m_sky);

	SAFE_DELETE(m_bg);

	// 障害物
	SAFE_DELETE(m_stumbler);
	// 道路
	SAFE_DELETE(m_road);
	// ターゲット
	SAFE_DELETE(m_target);

	// シーン
	CScene::ReleaseAll();

	//----------------------------
	// サウンドの停止
	//----------------------------
	m_sound->Stop(CSound::SOUND_LABEL_GAMEBGM);
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
		// タイマー更新
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

		// 空の更新（スクロール）
		m_sky->Update();

		// プレイヤーの座標取得
		D3DXVECTOR2 playerPos = m_player->GetPos();

		m_stumbler->UnLinkStum();

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

			//パーティクルのスクロール
			m_player->ParticleScrol(scroll);

			// 障害物のスクロール
			m_stumbler->Scroll(scroll);
			m_target->Scroll(scroll);

			// 道路のスクロール
			m_road->Scroll(scroll);
		}
/*		else if(playerPos.x < 0)
		{
			float scroll = 0 - playerPos.x;

			// プレイヤーは画面左端に
			m_player->SetPosX(0);

			// 空のスクロール
			m_sky->Scroll(scroll * 0.01f);

			// 背景のスクロール
			m_bg->Scroll(scroll);

			//パーティクルのスクロール
			m_player->ParticleScrol(scroll);

			// 障害物のスクロール
			m_stumbler->Scroll(scroll);
			m_target->Scroll(scroll);

			// 道路のスクロール
			m_road->Scroll(scroll);
		}*/
	}

	//全当たり判定
	ColAll();

	//----------------------------
	// 画面遷移
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
	/*if(m_keyboard->GetTrigger(DIK_RETURN))
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}*/
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CGame::InitObject(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// 背景
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


	// 空
	m_sky = CSky::Create(device);
	// 背景
	m_bg = CBackgroundManager::Create(device,map);
	// 道路
	m_road = CRoadManager::Create(device,map);
	// 障害物
	m_stumbler = CStumManager::Create(device,map);
	m_target = CTargetManager::Create(device,map);


	//----------------------------
	// キャラクター
	//----------------------------
	//設定情報管理クラスからコスチューム情報と乗り物情報取得
	int local_costume_id=CConfigHolder::Get(CONFIG_COSTUME);
	int local_vehicle_id=CConfigHolder::Get(CONFIG_ASSY);

	//プレイヤーの生成
	m_player=CPlayer::Create(device,(CostumeID)local_costume_id,(VehicleID)local_vehicle_id);
	m_player->SetPos(120.0f,300.0f);
	m_player->SetKeyboard(m_keyboard);
	m_player->SetPadX(m_padX);

	// タイマー
	m_time = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(SCREEN_WIDTH * 0.78, SCREEN_HEIGHT * 0.01f);
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
}

//=============================================================================
// 全当たり判定
//=============================================================================
void CGame::ColAll()
{
	// ゴールと接触判定
	if( m_target->CheckHitGoal( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
	{
		m_player->PlayerReflash();
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}

	//プレイヤと障害物の当たり判定
	if(m_stumbler->CheckHit( m_player->GetHitPos() , m_player->GetHitSize() , CScene2D::POINT_CENTER ))
	{
		m_player->AddHP(-1);
	}

	//ライトニング判定
	if(m_player->isLitninng())
	{
		m_player->PaticleStart((CScene*)m_target->CheckHit(m_player->GetPos() , m_player->GetSize()*3.0f , CScene2D::POINT_CENTER ));
	}

	if(!m_player->isDeth_())
	{
		ColPlayer();
	}

	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//プレイヤが死んでる場合フェード開始
		if(m_player->isDeth_())
		{
			m_player->PlayerReflash(false);
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}
}

void CGame::ColPlayer()
{
	// プレイヤーと道路の当たり判定、押し戻し
	D3DXVECTOR2 tmp[2],newpos;

	//全道路との当たり判定を行う(tmp[0]=押し戻し量,tmp[1]=自機座標)
	tmp[0] = m_road->CheckHit( m_player->GetHitPos() , m_player->GetHitSize() , CScene2D::POINT_CENTER );
	tmp[1] = m_player->GetPos();

	//Y押し戻し適用しない
	newpos.x= tmp[0].x + tmp[1].x;
	newpos.y= tmp[0].y + tmp[1].y;

	//道路の上から当たった場合
	if(tmp[0].y<0)
	{
		if(!m_player->isGround_())
		{
			newpos.x= tmp[1].x;
			m_player->isGround_set(true);
		}
		//Yの速度を0にして重力を切る
		m_player->SetCanJump();
		m_player->SpdKill();
	}

	else
	{
		m_player->isGround_set(false);
	}

	//道路の下から当たった場合
	if(tmp[0].y>0)
	{
		m_player->SpdKill();
	}

	//自機の座標に適用
	m_player->SetPos(newpos);
}
