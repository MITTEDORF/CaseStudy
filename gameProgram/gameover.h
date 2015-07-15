//*****************************************************************************
//
// �Q�[���I�[�o�[��ʐ���N���X [gameover.h]
// Author :YUKI SAKAMOTO,KAUMA_OOIGAWA
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
#include "character_config.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D;

class CGameOver : CPhase
{
public:
	CGameOver(){};
	~CGameOver(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:
	typedef enum
	{
		SELECT_CUR_CHAPTER =0,
		SELECT_CUR_RETURN,
		SELECT_CUR_MAX
	}SELECT_CUR;

	static const float CHAPTER_BUTTON_WIDTH;
	static const float RETURN_BUTTON_WIDTH;
	static const float BUTTON_HIGHT;

	void ButtonSelect( void );
	void InitObject(LPDIRECT3DDEVICE9 device);

	int m_select_cur;
	int m_select_old;

	bool m_push_flag;

	CScene2D* m_Button[SELECT_CUR_MAX];

	// �X�N���[������w�i
	CScene2D* m_bg;
};

//=============================================================================
#endif
