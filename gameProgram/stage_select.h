//*****************************************************************************
//
// �X�e�[�W�I����ʐ���N���X [stage_selrect.h]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************
#ifndef _STAGE_SELECT_H
#define _STAGE_SELECT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"
#include "character_config.h"
#include "stage_select_conf.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D;

class CStageSelect : CPhase
{
public:

	CStageSelect(void){};
	~CStageSelect(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	//�w�i�Ɏg��2D�|���S��
	CScene2D* select_bg;
	CScene2D* select_object[STAGE_MAX];

	//�J�[�\���p
	CScene2D* m_cur;

	//���ݑI��ł���I�u�W�F�N�g
	int nowSelectObject;

	// �X��
	float move;

	//�f�o�b�O�p

private:
	void InitObject(LPDIRECT3DDEVICE9 device);

	void SelectObjectUpdate();

	void ObjectUpdate();

	void NullSetVariable(void)
	{
		nowSelectObject=0;
		move = -0.025f;
		select_bg=NULL;

		for(int i=0;i<STAGE_MAX;i++)
		{
			select_object[i]=NULL;
		}

		m_cur=NULL;
	}

};

#endif