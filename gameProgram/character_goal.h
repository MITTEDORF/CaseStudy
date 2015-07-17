//=============================================================================
//
// �v���C���[����N���X [character_player.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_GOAL_H
#define _CHARACTER_GOAL_H
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// �}�N��
//============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CCharacterGoal : public CScene2D
{
public:
	//�R���X�g���N�^
	CCharacterGoal(){NullSetValiable();};
	//�f�X�g���N�^
	~CCharacterGoal(){};

	//����������
	//������:�f�o�C�X
	//�߂�l  :�����������ǂ�����HRESULT�^�ŕԂ�
	HRESULT	Init(LPDIRECT3DDEVICE9 device);

	//�I������
	void	Uninit(void);

	//�X�V����
	void	Update(void);

	//�`�揈��
	void	Draw(void);

	bool isFade_()
	{
		return (isFade);
	}
	bool isStart_()
	{
		return (isStart);
	}

	void Start(CScene* Target);

	static CCharacterGoal* Create(LPDIRECT3DDEVICE9 device);

private:
	CScene2D* CharacterL;
	CScene2D* CharacterR;

	CScene* target;

	bool isFade;
	bool isStart;

	float lenL;
	float lenR;

	int Cunt;

	void NullSetValiable()
	{
		isStart=false;
		isFade=false;
		Cunt=0;
		lenL=0;
		lenR=0;
		CharacterL=NULL;
		CharacterR=NULL;
		target=NULL;
	}



};

#endif

