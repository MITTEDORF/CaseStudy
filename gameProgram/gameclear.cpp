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

	// 背景スクロール処理
	D3DXVECTOR2 tmp;
	float scroll = 0.002;
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
void CGameClear::Draw(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CGameClear::InitObject(LPDIRECT3DDEVICE9 device)
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

		m_window[0] = CScene2D::Create(device, CImport::RESULT_WINDOW_BG, CScene2D::POINT_LEFTTOP);
		m_window[0]->SetSize(870.0f,500.0f);
		m_window[0]->SetPos(40, 40);

		m_window[1] = CScene2D::Create(device, CImport::CLOCK, CScene2D::POINT_LEFTTOP);
		m_window[1]->SetSize(100.0f,100.0f);
		m_window[1]->SetPos(80, 95);

		m_window[2] = CScene2D::Create(device, CImport::ASSY_TRUCK, CScene2D::POINT_LEFTTOP);
		m_window[2]->SetSize(120.0f,120.0f);
		m_window[2]->SetPos(80, 225);
		m_window[2]->SetCord( 0 , D3DXVECTOR2( 0.0f , 0.0f ) );
		m_window[2]->SetCord( 1 , D3DXVECTOR2( 0.25f , 0.0f ) );
		m_window[2]->SetCord( 2 , D3DXVECTOR2( 0.0f , 0.33f ) );
		m_window[2]->SetCord( 3 , D3DXVECTOR2( 0.25f , 0.33f ) );

		m_window[3] = CScene2D::Create(device, CImport::SCORE, CScene2D::POINT_LEFTTOP);
		m_window[3]->SetSize(300.0f,100.0f);
		m_window[3]->SetPos(125, 385);

		int score = 123456;
		D3DXVECTOR2 pos = D3DXVECTOR2(510,80);
		D3DXVECTOR2 size = D3DXVECTOR2(60,100);
		D3DXVECTOR2 i = D3DXVECTOR2(60,0);

		m_window[4] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_window[4]->SetSize(size);
		m_window[4]->SetPos(pos);
		m_window[4]->SetCord( 0 , D3DXVECTOR2( ( (score/100000) % 10 ) * 0.1, 0));
		m_window[4]->SetCord( 1 , D3DXVECTOR2( ( (score/100000) % 10 ) * 0.1 + 0.1, 0));
		m_window[4]->SetCord( 2 , D3DXVECTOR2( ( (score/100000) % 10 ) * 0.1, 1));
		m_window[4]->SetCord( 3 , D3DXVECTOR2( ( (score/100000) % 10 ) * 0.1 + 0.1, 1));

		m_window[5] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_window[5]->SetSize(size);
		m_window[5]->SetPos(pos + i);
		m_window[5]->SetCord( 0 , D3DXVECTOR2( ( (score/10000) % 10 ) * 0.1, 0));
		m_window[5]->SetCord( 1 , D3DXVECTOR2( ( (score/10000) % 10 ) * 0.1 + 0.1, 0));
		m_window[5]->SetCord( 2 , D3DXVECTOR2( ( (score/10000) % 10 ) * 0.1, 1));
		m_window[5]->SetCord( 3 , D3DXVECTOR2( ( (score/10000) % 10 ) * 0.1 + 0.1, 1));

		m_window[6] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_window[6]->SetSize(size);
		m_window[6]->SetPos(pos + i*2);
		m_window[6]->SetCord( 0 , D3DXVECTOR2( ( (score/1000) % 10 ) * 0.1, 0));
		m_window[6]->SetCord( 1 , D3DXVECTOR2( ( (score/1000) % 10 ) * 0.1 + 0.1, 0));
		m_window[6]->SetCord( 2 , D3DXVECTOR2( ( (score/1000) % 10 ) * 0.1, 1));
		m_window[6]->SetCord( 3 , D3DXVECTOR2( ( (score/1000) % 10 ) * 0.1 + 0.1, 1));

		m_window[7] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_window[7]->SetSize(size);
		m_window[7]->SetPos(pos + i*3);
		m_window[7]->SetCord( 0 , D3DXVECTOR2( ( (score/100) % 10 ) * 0.1, 0));
		m_window[7]->SetCord( 1 , D3DXVECTOR2( ( (score/100) % 10 ) * 0.1 + 0.1, 0));
		m_window[7]->SetCord( 2 , D3DXVECTOR2( ( (score/100) % 10 ) * 0.1, 1));
		m_window[7]->SetCord( 3 , D3DXVECTOR2( ( (score/100) % 10 ) * 0.1 + 0.1, 1));

		m_window[8] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_window[8]->SetSize(size);
		m_window[8]->SetPos(pos + i*4);
		m_window[8]->SetCord( 0 , D3DXVECTOR2( ( (score/10) % 10 ) * 0.1, 0));
		m_window[8]->SetCord( 1 , D3DXVECTOR2( ( (score/10) % 10 ) * 0.1 + 0.1, 0));
		m_window[8]->SetCord( 2 , D3DXVECTOR2( ( (score/10) % 10 ) * 0.1, 1));
		m_window[8]->SetCord( 3 , D3DXVECTOR2( ( (score/10) % 10 ) * 0.1 + 0.1, 1));

		m_window[9] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_window[9]->SetSize(size);
		m_window[9]->SetPos(pos + i*5);
		m_window[9]->SetCord( 0 , D3DXVECTOR2( ( (score/1) % 10 ) * 0.1, 0));
		m_window[9]->SetCord( 1 , D3DXVECTOR2( ( (score/1) % 10 ) * 0.1 + 0.1, 0));
		m_window[9]->SetCord( 2 , D3DXVECTOR2( ( (score/1) % 10 ) * 0.1, 1));
		m_window[9]->SetCord( 3 , D3DXVECTOR2( ( (score/1) % 10 ) * 0.1 + 0.1, 1));
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