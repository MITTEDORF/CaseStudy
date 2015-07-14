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

#include "stage_select.h"
#include "game.h"

#include "inputKeyboard.h"
#include <math.h>

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
	// スコア系初期化
	//----------------------------
	m_timescore = 300000 - m_time;
	m_assyscore = m_assyLife * 30000;
	m_score = m_timescore + m_assyscore;
	m_switch = 0;
	m_scoredest = 0;

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

		// スコア処理
		switch(m_switch)
		{
		case 0:		// タイムのスコア
			if(m_scoredest < m_timescore)
			{
				m_scoredest += m_timescore / 120 + 1;
				UpdateTimePol(m_scoredest);
			}
			else
			{
				m_scoredest = m_timescore;
				UpdateTimePol(m_scoredest);
				m_scoredest = 0;
				m_switch = 1;
			}
			break;
		case 1:		// 残体力のスコア
			if(m_scoredest < m_assyscore)
			{
				m_scoredest += m_assyscore / 120 + 1;
				UpdateAssyPol(m_scoredest);
			}
			else
			{
				m_scoredest = m_assyscore;
				UpdateAssyPol(m_scoredest);
				m_scoredest = 0;
				m_switch = 2;
			}
			break;
		case 2:		// 総スコア
			if(m_scoredest < m_score)
			{
				m_scoredest += m_score / 120 + 1;
				UpdateScorePol(m_scoredest);
			}
			else
			{
				m_scoredest = m_score;
				UpdateScorePol(m_scoredest);
				m_scoredest = 0;
				m_switch = 3;
			}
			break;
		default:
			break;
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
	resultLogo->SetSize(602.0f/2, 664.5f/2);
	resultLogo->SetPos(940.0f , 100.0f);

	/*CScene2D* resultLogo2 = CScene2D::Create(device, CImport::GOAL_CLEAR, CScene2D::POINT_LEFTTOP);
	resultLogo2->SetSize(SCREEN_WIDTH*0.25f-30.0f, SCREEN_WIDTH*0.25f-30.0f);
	resultLogo2->SetPos(45.0f+SCREEN_WIDTH*0.625f-30.0f, SCREEN_HEIGHT * 0.25f);*/

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

	// スコア表示用ウィンドウ
	m_window[0] = CScene2D::Create(device, CImport::RESULT_WINDOW_BG, CScene2D::POINT_LEFTTOP);
	m_window[0]->SetSize(870.0f,500.0f);
	m_window[0]->SetPos(40.0f, 40.0f);

	// 時計アイコン
	m_window[1] = CScene2D::Create(device, CImport::CLOCK, CScene2D::POINT_LEFTTOP);
	m_window[1]->SetSize(100.0f,100.0f);
	m_window[1]->SetPos(80.0f, 95.0f);

	// 乗り物アイコン
	m_window[2] = CScene2D::Create(device, CImport::ASSY_TRUCK, CScene2D::POINT_LEFTTOP);
	m_window[2]->SetSize(100.0f,100.0f);
	m_window[2]->SetPos(80.0f, 225.0f);
	m_window[2]->SetCord( 0 , D3DXVECTOR2( 0.0f , 0.0f ) );
	m_window[2]->SetCord( 1 , D3DXVECTOR2( 0.25f , 0.0f ) );
	m_window[2]->SetCord( 2 , D3DXVECTOR2( 0.0f , 0.33f ) );
	m_window[2]->SetCord( 3 , D3DXVECTOR2( 0.25f , 0.33f ) );

	// スコア文字
	m_window[3] = CScene2D::Create(device, CImport::SCORE, CScene2D::POINT_LEFTTOP);
	m_window[3]->SetSize(300.0f,100.0f);
	m_window[3]->SetPos(125.0f, 385.0f);

	// 時間によるスコア表示用ポリゴン初期化
	SetTimeScorePol(device, D3DXVECTOR2(510.0f, 95.0f), D3DXVECTOR2(60.0f, 100.0f));
	// 乗り物の状態によるスコア表示用ポリゴン初期化
	SetAssyScorePol(device, D3DXVECTOR2(510.0f, 225.0f), D3DXVECTOR2(60.0f, 100.0f));
	// 総スコア表示用ポリゴン初期化
	SetScorePol(device, D3DXVECTOR2(510.0f, 385.0f), D3DXVECTOR2(60.0f, 100.0f));
	// クリア時の時間表示用初期化
	SetTimePol(device, D3DXVECTOR2(190.0f, 95.0f), D3DXVECTOR2(60.0f, 100.0f));
	// クリア時の残体力表示用初期化
	SetAssyPol(device, D3DXVECTOR2(290.0f, 225.0f), D3DXVECTOR2(90.0f, 100.0f));
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

//=============================================================================
// 時間によるスコア表示用ポリゴンセット処理
//=============================================================================
void CGameClear::SetTimeScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	D3DXVECTOR2 offset = D3DXVECTOR2(size.x,0);

	for(int i = 0; i < 6; i++)
	{
		m_timeScorePol[i] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_timeScorePol[i]->SetSize(size);
		m_timeScorePol[i]->SetPos(pos + offset * (FLOAT)i);
		m_timeScorePol[i]->SetCord( 0, D3DXVECTOR2(0.0f, 0.0f));
		m_timeScorePol[i]->SetCord( 1, D3DXVECTOR2(0.1f, 0.0f));
		m_timeScorePol[i]->SetCord( 2, D3DXVECTOR2(0.0f, 1.0f));
		m_timeScorePol[i]->SetCord( 3, D3DXVECTOR2(0.1f, 1.0f));
	}
}

//=============================================================================
// 時間によるスコア表示用ポリゴン更新処理
//=============================================================================
void CGameClear::UpdateTimePol(int score)
{
	for(int i = 0; i < 6; i++)
	{
		m_timeScorePol[i]->SetCord( 0 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f,			0.0f));
		m_timeScorePol[i]->SetCord( 1 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f + 0.1f,	0.0f));
		m_timeScorePol[i]->SetCord( 2 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f,			1.0f));
		m_timeScorePol[i]->SetCord( 3 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f + 0.1f,	1.0f));
	}
}

//=============================================================================
// 乗り物の状態によるスコア表示用ポリゴンセット処理
//=============================================================================
void CGameClear::SetAssyScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	D3DXVECTOR2 offset = D3DXVECTOR2(size.x,0);

	for(int i = 0; i < 6; i++)
	{
		m_assyScorePol[i] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_assyScorePol[i]->SetSize(size);
		m_assyScorePol[i]->SetPos(pos + offset * (FLOAT)i);
		m_assyScorePol[i]->SetCord( 0, D3DXVECTOR2(0.0f, 0.0f));
		m_assyScorePol[i]->SetCord( 1, D3DXVECTOR2(0.1f, 0.0f));
		m_assyScorePol[i]->SetCord( 2, D3DXVECTOR2(0.0f, 1.0f));
		m_assyScorePol[i]->SetCord( 3, D3DXVECTOR2(0.1f, 1.0f));
	}
}

//=============================================================================
// 乗り物の状態によるスコア表示用ポリゴン更新処理
//=============================================================================
void CGameClear::UpdateAssyPol(int score)
{
	for(int i = 0; i < 6; i++)
	{
		m_assyScorePol[i]->SetCord( 0 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f,			0.0f));
		m_assyScorePol[i]->SetCord( 1 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f + 0.1f,	0.0f));
		m_assyScorePol[i]->SetCord( 2 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f,			1.0f));
		m_assyScorePol[i]->SetCord( 3 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f + 0.1f,	1.0f));
	}
}

//=============================================================================
// 総スコア表示用ポリゴンセット処理
//=============================================================================
void CGameClear::SetScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	D3DXVECTOR2 offset = D3DXVECTOR2(size.x,0);

	for(int i = 0; i < 6; i++)
	{
		m_ScorePol[i] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
		m_ScorePol[i]->SetSize(size);
		m_ScorePol[i]->SetPos(pos + offset * (FLOAT)i);
		m_ScorePol[i]->SetCord( 0, D3DXVECTOR2(0.0f, 0.0f));
		m_ScorePol[i]->SetCord( 1, D3DXVECTOR2(0.1f, 0.0f));
		m_ScorePol[i]->SetCord( 2, D3DXVECTOR2(0.0f, 1.0f));
		m_ScorePol[i]->SetCord( 3, D3DXVECTOR2(0.1f, 1.0f));
	}
}

//=============================================================================
// 総スコア表示用ポリゴン更新処理
//=============================================================================
void CGameClear::UpdateScorePol(int score)
{
	for(int i = 0; i < 6; i++)
	{
		m_ScorePol[i]->SetCord( 0 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f,			0.0f));
		m_ScorePol[i]->SetCord( 1 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f + 0.1f,	0.0f));
		m_ScorePol[i]->SetCord( 2 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f,			1.0f));
		m_ScorePol[i]->SetCord( 3 , D3DXVECTOR2( ( (score/(100000/(int)pow(10.0f,i))) % 10 ) * 0.1f + 0.1f,	1.0f));
	}
}

//=============================================================================
// クリア時間表示用ポリゴンセット処理
//=============================================================================
void CGameClear::SetTimePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	D3DXVECTOR2 offset = D3DXVECTOR2(size.x,0);

	for(int i = 0; i < 5; i++)
	{
		m_timePol[i] = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);

		m_timePol[i]->SetSize(size);
		m_timePol[i]->SetPos(pos + offset * (FLOAT)i);

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
			m_timePol[i]->SetTex(CImport::COLON);
		}
	}

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
}

//=============================================================================
// クリア時残体力表示用ポリゴンセット処理
//=============================================================================
void CGameClear::SetAssyPol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	m_assyPol = CScene2D::Create(device, CImport::NUMBER, CScene2D::POINT_LEFTTOP);
	m_assyPol->SetSize(size);
	m_assyPol->SetPos(pos);
	m_assyPol->SetTex(CImport::NUMBER);
	m_assyPol->SetCord(0, D3DXVECTOR2( (m_assyLife % 10) * 0.1f,			0.0f));
	m_assyPol->SetCord(1, D3DXVECTOR2( (m_assyLife % 10) * 0.1f + 0.1f,		0.0f));
	m_assyPol->SetCord(2, D3DXVECTOR2( (m_assyLife % 10) * 0.1f,			1.0f));
	m_assyPol->SetCord(3, D3DXVECTOR2( (m_assyLife % 10) * 0.1f + 0.1f,		1.0f));
}