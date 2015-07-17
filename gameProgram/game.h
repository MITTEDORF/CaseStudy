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

	//�S�����蔻��
	void ColAll();

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

	CCharacterGoal* m_char_goal;

	// �o�ߎ���
	int m_time;
	// �o�ߎ��ԕ\���|���S��
	CScene2D* m_timePol[5];
	CScene2D* m_countdown[2];
	int m_sequence;
};

//=============================================================================
#endif
