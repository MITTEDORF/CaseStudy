//*****************************************************************************
//
// ゲームクリア画面制御クラス [gameclear.h]
// Author :YUKI SAKAMOTO,OOIGAWA KAZUMA
//
//*****************************************************************************

#ifndef _MY_GAMECLEAR_H
#define _MY_GAMECLEAR_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"
#include "character_config.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D;

class CGameClear : CPhase
{
public:
	CGameClear(int time, int life)
	{
		//--------------------------------------------------
		// ゲームから渡されてきたステータスを保存
		//--------------------------------------------------
		m_time = time;
		m_assyLife = life;
	};
	~CGameClear(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:
	typedef enum
	{
		SELECT_CUR_CHAPTER =0,
		//SELECT_CUR_NEXTSTAGE,
		SELECT_CUR_RETURN,
		SELECT_CUR_MAX
	}SELECT_CUR;

	static const float CHAPTER_BUTTON_WIDTH;
	static const float NEXTSTAGE_BUTTON_WIDTH;
	static const float RETURN_BUTTON_WIDTH;
	static const float BUTTON_HIGHT;

	int m_select_cur;
	int m_select_old;

	bool m_push_flag;

	void ButtonSelect( void );
	void InitObject(LPDIRECT3DDEVICE9 device);

	CScene2D* m_Button[SELECT_CUR_MAX];

	CScene2D* m_window[5];

	// クリア時の時間表示用
	CScene2D* m_timePol[5];
	void SetTimePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	int m_time;

	// クリア時の残体力表示用
	CScene2D* m_assyPol;
	void SetAssyPol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	int m_assyLife;

	// 時間によるスコア表示用
	CScene2D* m_timeScorePol[6];
	void SetTimeScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void UpdateTimePol(int score);
	int m_timescore;
	int m_scoredest;
	char m_switch;

	// 乗り物の状態によるスコア表示用
	CScene2D* m_assyScorePol[6];
	void SetAssyScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void UpdateAssyPol(int score);
	int m_assyscore;

	// 最終的なスコア表示用
	CScene2D* m_ScorePol[6];
	void SetScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void UpdateScorePol(int score);
	int m_score;

	// スクロールする背景
	CScene2D* m_bg;
};

//=============================================================================
#endif
