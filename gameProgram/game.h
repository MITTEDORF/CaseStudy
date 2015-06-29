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

	//�S�����蔻��
	void ColAll();

	// �o�[�W�����\��
	CScene2D* m_version;

	//�v���C���[����
	CPlayer *m_player;

	// �w�i
	CSky*				m_sky;
	CBackgroundManager* m_bg;

	// ��Q��
	CStumManager* m_stumbler;

	// ���H
	CRoadManager* m_road;

	// �^�[�Q�b�g
	CTargetManager* m_target;
};

//=============================================================================
#endif
