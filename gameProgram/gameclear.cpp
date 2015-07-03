//*****************************************************************************
//
// ゲームクリア画面制御クラス [gameclear.cpp]
// Author :YUKI SAKAMOTO,OOIGAWA_KAZUMA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "gameclear.h"
#include "manager.h"
#include "fade.h"

#include "title.h"
#include "game.h"

#include "inputKeyboard.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const float CGameClear::CHAPTER_BUTTON_WIDTH = 445.0f;
const float CGameClear::NEXTSTAGE_BUTTON_WIDTH = 336.0f;
const float CGameClear::RETURN_BUTTON_WIDTH = 247.0f;
const float CGameClear::BUTTON_HIGHT = 75.0f;

//============================================================================
// 初期化
//=============================================================================
HRESULT CGameClear::Init(LPDIRECT3DDEVICE9 device)
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
	// ボタンカーソル初期化
	//----------------------------
	m_select_cur = SELECT_CUR_CHAPTER;

	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGameClear::Uninit(void)
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
void CGameClear::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//----------------------------
		// ボタンテクスチャ変更
		//----------------------------
		ButtonSelect();
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
		if( m_select_cur == SELECT_CUR_RETURN )
		{
			CManager::SetNextPhase((CPhase*)new CGame(costume_id, vehicle_id));
		}
		else
		{
			CManager::SetNextPhase((CPhase*)new CTitle);
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CGameClear::Draw(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CGameClear::InitObject(LPDIRECT3DDEVICE9 device)
{

	CScene2D* resultLogo = CScene2D::Create(device, CImport::PLAYER_GOODMOOD, CScene2D::POINT_LEFTTOP);
		resultLogo->SetSize(602, 664.5f);
		resultLogo->SetPos(15.0f , SCREEN_HEIGHT * 0.125f*0.5f);

		CScene2D* resultLogo2 = CScene2D::Create(device, CImport::GOAL_CLEAR, CScene2D::POINT_LEFTTOP);
		resultLogo2->SetSize(SCREEN_WIDTH*0.25f-30.0f, SCREEN_WIDTH*0.25f-30.0f);
		resultLogo2->SetPos(45.0f+SCREEN_WIDTH*0.625f-30.0f, SCREEN_HEIGHT * 0.25f);

		m_Button[SELECT_CUR_CHAPTER] = CScene2D::Create(device, "data/TEXTURE/button/chapterSelect.png" , CScene2D::POINT_LEFTTOP);
		m_Button[SELECT_CUR_CHAPTER]->SetSize( CHAPTER_BUTTON_WIDTH , BUTTON_HIGHT );
		m_Button[SELECT_CUR_CHAPTER]->SetPos( 60.0f , 576.0f);
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );

		m_Button[SELECT_CUR_NEXTSTAGE] = CScene2D::Create(device, "data/TEXTURE/button/nextStage.png" , CScene2D::POINT_LEFTTOP);
		m_Button[SELECT_CUR_NEXTSTAGE]->SetSize( NEXTSTAGE_BUTTON_WIDTH , BUTTON_HIGHT );
		m_Button[SELECT_CUR_NEXTSTAGE]->SetPos( 565.0f , 576.0f);
		m_Button[SELECT_CUR_NEXTSTAGE]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_NEXTSTAGE]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_NEXTSTAGE]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
		m_Button[SELECT_CUR_NEXTSTAGE]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );

		m_Button[SELECT_CUR_RETURN] = CScene2D::Create(device, "data/TEXTURE/button/retry.png" , CScene2D::POINT_LEFTTOP);
		m_Button[SELECT_CUR_RETURN]->SetSize( RETURN_BUTTON_WIDTH , BUTTON_HIGHT );
		m_Button[SELECT_CUR_RETURN]->SetPos( 961.0f , 576.0f);
		m_Button[SELECT_CUR_RETURN]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_RETURN]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_RETURN]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
		m_Button[SELECT_CUR_RETURN]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );

}
//=============================================================================
// ボタンUV変更処理
//=============================================================================
void CGameClear::ButtonSelect( void )
{

	if(m_keyboard->GetTrigger(DIK_A))
	{
		if( m_select_cur-1 >= 0 )
		{
			m_select_cur--;
		}
		else
		{
			m_select_cur = SELECT_CUR_MAX-1;
		}
	}
	if(m_keyboard->GetTrigger(DIK_D))
	{
		if( m_select_cur+1 <= SELECT_CUR_MAX-1 )
		{
			m_select_cur++;
		}
		else
		{
			m_select_cur = 0;
		}
	}
	if( m_select_old == m_select_cur )
	{
		return;
	}
	else
	{
		for( int loop = 0 ; loop < SELECT_CUR_MAX ; loop++ )
		{
			m_Button[loop]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*0 ) );
			m_Button[loop]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*0 ) );
			m_Button[loop]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
			m_Button[loop]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );
		}
		if( m_push_flag )
		{
			m_Button[m_select_cur]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*2 ) );
			m_Button[m_select_cur]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*2 ) );
			m_Button[m_select_cur]->SetCord( 2 , D3DXVECTOR2( 0.0f , 1.0f ) );
			m_Button[m_select_cur]->SetCord( 3 , D3DXVECTOR2( 1.0f , 1.0f ) );
		}
		else
		{
			m_Button[m_select_cur]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
			m_Button[m_select_cur]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );
			m_Button[m_select_cur]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*2 ) );
			m_Button[m_select_cur]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*2 ) );
		}
	}
	m_select_old = m_select_cur;

}