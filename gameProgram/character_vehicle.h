//=============================================================================
//
// ��蕨����N���X [character_vehicle.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_VEHICLE_H
#define _CHARACTER_VEHICLE_H
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// �}�N��
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CVehicle : public CScene2D
{
public:
	//�R���X�g���N�^
	//������:�v���C�I���e�B(�ő��PRIORITY_MAX�A�������͂��Ȃ���PRIORITY_MAX - 2�ɐݒ�)
	//������:�I�u�W�F�N�g�^�C�v(�������͂��Ȃ���OBJTYPE_NONE�ɐݒ�)
	CVehicle(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//�f�X�g���N�^
	~CVehicle(){};

	//�N���G�C�g
	//������:�f�o�C�X
	//������:�e�N�X�`�����
	//�߂�l  :�C���X�^���X�̃|�C���^
	static CVehicle* Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);

	//����������
	//������:�f�o�C�X
	//������:�e�N�X�`�����
	//�߂�l  :�����������ǂ�����HRESULT�^�ŕԂ�
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);

	//�I������
	void	Uninit(void);

	//�X�V����
	void	Update(void);

	//�`�揈��
	void	Draw(void);

private:
	//���݂̃A�j���[�V�������[�h
	int AnimMode;
	//�A�j���[�V�����̃��[�v�t���O
	bool isRupeAnim;
	//�A�j���[�V������1���I���t���O
	bool isAnimEnd;

	//���݂̃A�j���[�V�����ԍ�
	int nowAnim;
	//�A�j���[�V�����̃J�E���g�p
	int cntAnim;
	//�A�j���[�V�����̍ő�R�}��
	int maxAnim;

	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		maxAnim=0;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=0;
		cntAnim=0;
		nowAnim=1;
	}

	//�A�j���[�V�����̍X�V����
	void UpdateAnim();
	//�A�j���[�V�����̃Z�b�g����
	void SetAnimMode(int animID,bool Rupe);
};

#endif

