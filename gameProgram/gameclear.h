//*****************************************************************************
//
// �Q�[���N���A��ʐ���N���X [gameclear.h]
// Author :YUKI SAKAMOTO,OOIGAWA KAZUMA
//
//*****************************************************************************

#ifndef _MY_GAMECLEAR_H
#define _MY_GAMECLEAR_H
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

class CGameClear : CPhase
{
public:
	CGameClear(int time, int life)
	{
		//--------------------------------------------------
		// �Q�[������n����Ă����X�e�[�^�X��ۑ�
		//--------------------------------------------------
		m_time = time;
		m_assyLife = life;
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
		//SELECT_CUR_NEXTSTAGE,
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

	CScene2D* m_window[5];

	// �N���A���̎��ԕ\���p
	CScene2D* m_timePol[5];
	void SetTimePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	int m_time;

	// �N���A���̎c�̗͕\���p
	CScene2D* m_assyPol;
	void SetAssyPol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	int m_assyLife;

	// ���Ԃɂ��X�R�A�\���p
	CScene2D* m_timeScorePol[6];
	void SetTimeScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void UpdateTimePol(int score);
	int m_timescore;
	int m_scoredest;
	char m_switch;

	// ��蕨�̏�Ԃɂ��X�R�A�\���p
	CScene2D* m_assyScorePol[6];
	void SetAssyScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void UpdateAssyPol(int score);
	int m_assyscore;

	// �ŏI�I�ȃX�R�A�\���p
	CScene2D* m_ScorePol[6];
	void SetScorePol(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void UpdateScorePol(int score);
	int m_score;

	// �X�N���[������w�i
	CScene2D* m_bg;
};

//=============================================================================
#endif
