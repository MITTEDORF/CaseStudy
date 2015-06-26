//*****************************************************************************
//
// ゲームオーバー画面制御クラス [gameover.cpp]
// Author :YUKI SAKAMOTO,KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "gameover.h"
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
const float CGameOver::CHAPTER_BUTTON_WIDTH = 445.0f;
const float CGameOver::RETURN_BUTTON_WIDTH = 247.0f;
const float CGameOver::BUTTON_HIGHT = 75.0f;
//=============================================================================
// 初期化
//=============================================================================
HRESULT CGameOver::Init(LPDIRECT3DDEVICE9 device)
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
void CGameOver::Uninit(void)
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
void CGameOver::Update(void)
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
			m_push_flag = true;
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
void CGameOver::Draw(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CGameOver::InitObject(LPDIRECT3DDEVICE9 device)
{

	//ゲームオーバー画面
		CScene2D* resultLogo = CScene2D::Create(device, CImport::PLAYER_BADMOOD, CScene2D::POINT_CENTER);
		resultLogo->SetSize(743.0f*0.5f, 1274.0f*0.5f);
		resultLogo->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

		m_Button[SELECT_CUR_CHAPTER] = CScene2D::Create(device, "data/TEXTURE/button/chapterSelect.png" , CScene2D::POINT_LEFTTOP);
		m_Button[SELECT_CUR_CHAPTER]->SetSize( CHAPTER_BUTTON_WIDTH , BUTTON_HIGHT );
		m_Button[SELECT_CUR_CHAPTER]->SetPos( 213.0f , 576.0f);
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
		m_Button[SELECT_CUR_CHAPTER]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );

		m_Button[SELECT_CUR_RETURN] = CScene2D::Create(device, "data/TEXTURE/button/retry.png" , CScene2D::POINT_LEFTTOP);
		m_Button[SELECT_CUR_RETURN]->SetSize( RETURN_BUTTON_WIDTH , BUTTON_HIGHT );
		m_Button[SELECT_CUR_RETURN]->SetPos( 753.0f , 576.0f);
		m_Button[SELECT_CUR_RETURN]->SetCord( 0 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_RETURN]->SetCord( 1 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*0 ) );
		m_Button[SELECT_CUR_RETURN]->SetCord( 2 , D3DXVECTOR2( 0.0f , ( 1.0f / 3.0f )*1 ) );
		m_Button[SELECT_CUR_RETURN]->SetCord( 3 , D3DXVECTOR2( 1.0f , ( 1.0f / 3.0f )*1 ) );
}
//=============================================================================
// ボタンUV変更処理
//=============================================================================
void CGameOver::ButtonSelect( void )
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