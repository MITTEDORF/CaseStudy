//*****************************************************************************
//
// CGameクラス [game.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_GAME_H
#define _MY_GAME_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"
#include "character_config.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D;
class CPlayer;
class CSky;
class CBackgroundManager;
class CStumManager;
class CRoadManager;
class CTargetManager;
class CGoal;
class CCharacterGoal;

class CGame : CPhase
{
public:
	CGame(){};
	~CGame(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:
	void InitObject(LPDIRECT3DDEVICE9 device);
	void Debug(void);

	void ColPlayer();

	//全当たり判定
	void ColAll();

	//プレイヤー制御
	CPlayer *m_player;

	// 背景
	CSky*				m_sky;
	CBackgroundManager* m_bg;

	// 障害物
	CStumManager* m_stumbler;

	// 道路
	CRoadManager* m_road;

	// ターゲット
	CTargetManager* m_target;

	CCharacterGoal* m_char_goal;

	// 経過時間
	int m_time;
	// 経過時間表示ポリゴン
	CScene2D* m_timePol[5];
	CScene2D* m_countdown[2];
	int m_sequence;
};

//=============================================================================
#endif
