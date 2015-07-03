//*****************************************************************************
//
// 装備選択画面制御クラス [equipment_choice.h]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

#ifndef _EQUIPMENT_CHOICE_H
#define _EQUIPMENT_CHOICE_H
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
class CPlayer;

class CEquipmentChoice : CPhase
{
public:
	CEquipmentChoice(void){};
	~CEquipmentChoice(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:
	void InitObject(LPDIRECT3DDEVICE9 device);

	CScene2D* m_version;
	CScene2D* m_slotback;
	CScene2D* m_cur;
	CScene2D* m_cos;
	CScene2D* m_ass;
	CScene2D* bg;

	void VehicleChoice();
	void CostumeChoice();

	//プレイヤー制御
	CPlayer *m_player;

	int costume_id;
	int vehicle_id;
	int cntAnim;
	int nowAnim;

	void NullSetVariable(void)
	{
		cntAnim=0;
		nowAnim=1;
		m_player=NULL;
		m_slotback=NULL;
		bg=NULL;
		m_cos=NULL;
		m_ass=NULL;
		m_cur=NULL;
		costume_id=COSTUME_NONE;
		vehicle_id=VEHICLE_TRAM;
	}

	void AnimUpdate();

	void CurUpdate();

	void cosUpdate();

};

//=============================================================================
#endif
