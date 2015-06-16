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
struct LASER
{
	float Time;

	D3DXVECTOR2 Position;

	D3DXVECTOR2 ControlVector0;
	D3DXVECTOR2 ControlVector1;

	bool Use;
};
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
	void Draw(void);

	//�p�[�e�B�N���J�n����
	//������:�X�^�[�g���W
	//������:�ړI�̍��W
	void Start(D3DXVECTOR2 pos,CScene *target);

	//�p�[�e�B�N���j�󏈗�
	void Destroy();

	//�p�[�e�B�N���������Ă��邩�ǂ���
	//�߂�l:�p�[�e�B�N���̐���
	bool isLive()
	{
		return (m_Laser.Use);
	}

private:

	//���[�U�[�̓����ɕK�v�ȕϐ��Q
	LASER m_Laser;

	//�ڕW�̍��W
	CScene *objtarget;

	float Angle;


	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		Angle=0.0f;
		m_Laser.ControlVector0=D3DXVECTOR2(0.0f,0.0f);
		m_Laser.ControlVector1=D3DXVECTOR2(0.0f,0.0f);
		m_Laser.Position=D3DXVECTOR2(0.0f,0.0f);
		m_Laser.Time=0.0f;
		m_Laser.Use=false;
		objtarget=this;
	}
};

#endif

