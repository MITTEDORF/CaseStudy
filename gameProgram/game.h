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

class CGame : CPhase
{
public:
	CGame(CostumeID cos_id = COSTUME_NONE,VehicleID veh_id = VEHICLE_TRAM)
	{
		costume_id=cos_id;
		vehicle_id=veh_id;
	};
	~CGame(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:
	void InitObject(LPDIRECT3DDEVICE9 device);
	void Debug(void);

	CostumeID costume_id;
	VehicleID vehicle_id;

	//全当たり判定
	void ColAll();

	// バージョン表示
	CScene2D* m_version;

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
};

//=============================================================================
#endif
