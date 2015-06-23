//=============================================================================
//
// �p�[�e�B�N������N���X [particle_object.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _MINI_PARTICLE_OBJECT_H
#define _MINI_PARTICLE_OBJECT_H
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "particle_manager.h"
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
class CMiniParticleObject: public CScene2D
{
public:
	//�R���X�g���N�^
	//������:�v���C�I���e�B(�ő��PRIORITY_MAX�A�������͂��Ȃ���PRIORITY_MAX - 2�ɐݒ�)
	//������:�I�u�W�F�N�g�^�C�v(�������͂��Ȃ���OBJTYPE_NONE�ɐݒ�)
	CMiniParticleObject(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//�f�X�g���N�^
	~CMiniParticleObject(){};

	//�N���G�C�g
	//������:�f�o�C�X
	//�߂�l  :�C���X�^���X�̃|�C���^
	static CMiniParticleObject* Create(LPDIRECT3DDEVICE9 device);

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
	void Start(D3DXVECTOR2 pos);

	//�p�[�e�B�N���j�󏈗�
	void Destroy();

	//�p�[�e�B�N���������Ă��邩�ǂ���
	//�߂�l:�p�[�e�B�N���̐���
	bool isUse_()
	{
		return (isUse);
	}

	void Scrol(float value)
	{
		m_pos.x -=value;
		CScene2D::SetVertexPolygon();
	}
private:

	D3DXCOLOR m_color;

	float m_Rad;

	float Angle;

	bool isUse;

	float ColA;

	float Anglespd;



	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		Angle=0.0f;
		m_Rad=0;
		m_color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		isUse=false;
		ColA=1.0f;
		Anglespd=0;
	}
};

#endif

