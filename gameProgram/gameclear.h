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
	CGameClear(CostumeID cos_id = COSTUME_NONE,VehicleID veh_id = VEHICLE_TRAM)
	{
		costume_id=cos_id;
		vehicle_id=veh_id;
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
		SELECT_CUR_NEXTSTAGE,
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

	CScene2D* m_version;

	CostumeID costume_id;
	VehicleID vehicle_id;
};

//=============================================================================
#endif
