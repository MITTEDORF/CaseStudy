//=============================================================================
//
// �p�[�e�B�N������N���X [particle_object.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PARTICLE_OBJECT_H
#define _PARTICLE_OBJECT_H
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
class CParticleObject: public CScene2D
{
public:
	//�R���X�g���N�^
	//������:�v���C�I���e�B(�ő��PRIORITY_MAX�A�������͂��Ȃ���PRIORITY_MAX - 2�ɐݒ�)
	//������:�I�u�W�F�N�g�^�C�v(�������͂��Ȃ���OBJTYPE_NONE�ɐݒ�)
	CParticleObject(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//�f�X�g���N�^
	~CParticleObject(){};

	//�N���G�C�g
	//������:�f�o�C�X
	//�߂�l  :�C���X�^���X�̃|�C���^
	static CParticleObject* Create(LPDIRECT3DDEVICE9 device);

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

	//�p�[�e�B�N���J�n����
	void Start(D3DXVECTOR2 pos,D3DXVECTOR2 spd,int LiveTime);
	//�p�[�e�B�N���j�󏈗�
	void Destroy();

private:
	//�ړ��X�s�[�h
	D3DXVECTOR2 m_spd;
	//��������
	int LiveTime;
	//�����Ă��邩�ǂ���
	bool isDeth;
	//���݂�������
	int LiveCnt;


	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		LiveCnt=0;
		m_spd=D3DXVECTOR2(0.0f,0.0f);
		LiveTime=100;
		isDeth=true;
	}
};

#endif

