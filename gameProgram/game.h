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
class CPlayer;
class CSky;
class CBackground;
class CScene2D;
class CGoal;

class CGame : CPhase
{
public:
	CGame(CostumeID cos_id,VehicleID veh_id)
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

	//プレイヤー制御
	CPlayer *m_player;

	// 背景
	CSky*		 m_sky;
	CBackground* m_bg;

	CScene2D* m_version;

	// ゴール(大井川 6/2_12時頃追加)
	CGoal *m_Goal;
};

//=============================================================================
#endif
