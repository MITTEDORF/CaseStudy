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

#include "stage_select.h"
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
			CManager::SetNextPhase((CPhase*)new CGame());
		}
		else
		{
			CManager::SetNextPhase((CPhase*)new CStageSelect);
		}
	}

	// 背景スクロール処理
	D3DXVECTOR2 tmp;
	float scroll = 0.002f;
	for(int i = 0; i < 4;  i++)
	{
		tmp = m_bg->GetCord(i);
		tmp.y -= scroll;
		m_bg->SetCord(i, tmp);
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
	// 背景
	CScene2D* bg = CScene2D::Create(device, CImport::MAKE_UI_CHAR_SEL_BACK_01, CScene2D::POINT_LEFTTOP, 1);
	bg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	bg->SetPos(0.0f, 0.0f);

	// スクロールする背景
	m_bg = CScene2D::Create(device, CImport::MAKE_UI_CHAR_SEL_CHIP_01, CScene2D::POINT_CENTER, 2);
	m_bg->SetSize(SCREEN_WIDTH * 1.3, SCREEN_WIDTH * 1.3);
	m_bg->SetPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_bg->SetRot(-0.5f);

	//ゲームオーバー画面
	CScene2D* resultLogo = CScene2D::Create(device, CImport::PLAYER_BADMOOD, CScene2D::POINT_LEFTTOP);
		resultLogo->SetSize(371.5f + 27.5f , 637.0f + 27.5f );
		resultLogo->SetPos(15.0f * 15.0f , SCREEN_HEIGHT * 0.125f * 0.5f );

		CScene2D* resultLogo2 = CScene2D::Create(device, CImport::GOAL_OFF, CScene2D::POINT_LEFTTOP);
		resultLogo2->SetSize(SCREEN_WIDTH*0.25f-30.0f, SCREEN_WIDTH*0.25f-30.0f);
		resultLogo2->SetPos(45.0f+SCREEN_WIDTH*0.625f-30.0f, SCREEN_HEIGHT * 0.25f);

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