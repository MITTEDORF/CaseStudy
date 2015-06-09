//*****************************************************************************
//
// �Q�[���I�[�o�[��ʐ���N���X [gameover.h]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

#ifndef _MY_GAMEOVER_H
#define _MY_GAMEOVER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D;

class CGameOver : CPhase
{
public:
	CGameOver(void){};
	~CGameOver(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:
	void InitObject(LPDIRECT3DDEVICE9 device);

	CScene2D* m_version;
};

//=============================================================================
#endif