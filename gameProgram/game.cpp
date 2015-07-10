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
	m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);

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

	//----------------------------------------
	// 障害物関連（後で消してね
	SAFE_DELETE(m_stumbler);
	//----------------------------------------
	// 道路関連（後で消してね
	SAFE_DELETE(m_road);
	//----------------------------------------
	// ターゲット関連（後で消してね
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

			//----------------------------------------
			// 障害物関連（後で消してね
			m_stumbler->Scroll(scroll);
			m_road->Scroll(scroll);
			m_target->Scroll(scroll);

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

			//パーティクルのスクロール
			m_player->ParticleScrol(scroll);

			//----------------------------------------
			// 障害物関連（後で消してね
			m_stumbler->Scroll(scroll);
			m_road->Scroll(scroll);
			m_target->Scroll(scroll);
		}

		

		//α仮置き
		/*if( m_Goal->CheckCollisionAABB( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
		{
			m_player->PlayerReflash();
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}*/
		// ゴールと接触判定
		if( m_target->CheckHitGoal( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
		{
			m_player->PlayerReflash();
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
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
			CManager::SetNextPhase((CPhase*)new CGameOver(costume_id, vehicle_id));
		}

		else
		{
			CManager::SetNextPhase((CPhase*)new CGameClear(costume_id, vehicle_id));
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
	m_bg = CBackgroundManager::Create(device);

	//-----------------------------
	// 道路関連(後で修正してね
	m_road = CRoadManager::Create(device);
	//-----------------------------
	// 障害物関連(後で修正してね
	m_stumbler = CStumManager::Create(device);
	m_target = CTargetManager::Create(device);

	//----------------------------
	// キャラクター
	//----------------------------
	//プレイヤーの生成
	m_player=CPlayer::Create(device,costume_id,vehicle_id);
	m_player->SetPos(120.0f,300.0f);
	m_player->SetKeyboard(m_keyboard);
	m_player->SetPadX(m_padX);
}

//=============================================================================
// 全当たり判定
//=============================================================================
void CGame::ColAll()
{
	//プレイヤと障害物の当たり判定
	if(m_stumbler->CheckHit( m_player->GetHitPos() , m_player->GetHitSize() , CScene2D::POINT_CENTER ))
	{
		m_player->AddHP(-1);
	}

	//ライトニング判定
	if(m_player->isLitninng())
	{
		/*if((m_Goal->CheckCollisionAABB(m_player->GetPos() , m_player->GetSize()*3.0f , CScene2D::POINT_CENTER )))
		{
			m_player->PaticleStart(m_Goal);
		}

		else
		{
			m_player->PaticleStart(NULL);
		}*/
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
