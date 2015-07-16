//=============================================================================
//
// �p�[�e�B�N���Ǘ��N���X [particle_manager.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PARTICLE_MANAGER_H
#define _PARTICLE_MANAGER_H
//=============================================================================
// �C���N���[�h
//============================================================================
#include "particle_object.h"
//=============================================================================
// �}�N��
//============================================================================
//�p�[�e�B�N����
const int PARTICLE_MAX            = 40;
//�f�B���C
const int PARTICLE_COOL_DOWN_TIME = 10;
//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CParticleManager
{
public:
	CParticleManager();
	~CParticleManager();

	//������
	void Init(LPDIRECT3DDEVICE9 device);

	//�p�[�e�B�N���I�u�W�F�N�g�̎擾
	//������:�擾�������p�[�e�B�N����ID
	CParticleObject* object_(int id)
	{
		return (object[id]);
	}

	//�p�[�e�B�N���̐����J�n(�V�����V�����V�����Ɣ�΂�)
	//������:�ړI�n�̍��W(�����ɔ�΂������ꍇ�͎����̍��W������)
	void Start(CScene* target);

	//�p�[�e�B�N���̐����J�n(�h�o�[�b�Ɣ�΂�)
	//������:�ړI�n�̍��W(�����ɔ�΂������ꍇ�͎����̍��W������)
	void StartBurst(CScene* target);

	//�S�p�[�e�B�N���̒�~
	void StopALL();

	bool IsUsing()
	{
		return (object[0]->isLive());
	}

	//�v���C���[�̍��W�̃Z�b�g
	void Setpos(D3DXVECTOR2 pos);

	void Scrol(float value)
	{
		for(int i=0;i<PARTICLE_MAX-1;i++)
		{
			object[i]->Scrol(value);
		}
	}

private:
	//�p�[�e�B�N���I�u�W�F�N�g
	CParticleObject* object[PARTICLE_MAX];
	//�����ʒu
	D3DXVECTOR2 m_pos;
	//�f�B���C
	int coolDownTinme;
};

#endif

