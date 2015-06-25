//*****************************************************************************
//
// CGame�N���X [game.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_GAME_H
#define _MY_GAME_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"
#include "character_config.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
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

	//�S�����蔻��
	void ColAll();

	//�v���C���[����
	CPlayer *m_player;

	// �w�i
	CSky*		 m_sky;
	CBackground* m_bg;

	CScene2D* m_version;

	// �S�[��(���� 6/2_12�����ǉ�)
	CGoal *m_Goal;
};

//=============================================================================
#endif
