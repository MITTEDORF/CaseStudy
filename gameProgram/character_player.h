//=============================================================================
//
// �v���C���[����N���X [character_player.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_PLAYER_H
#define _CHARACTER_PLAYER_H
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
//�L�[�{�[�h���͐���N���X
class CInputKeyboard;

//=============================================================================
// �N���X��`
//=============================================================================
class CPlayer : public CScene2D
{
public:
	//�R���X�g���N�^
	//������:�v���C�I���e�B(�ő��PRIORITY_MAX�A�������͂��Ȃ���PRIORITY_MAX - 2�ɐݒ�)
	//������:�I�u�W�F�N�g�^�C�v(�������͂��Ȃ���OBJTYPE_NONE�ɐݒ�)
	CPlayer(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//�f�X�g���N�^
	~CPlayer(){};

	//�N���G�C�g
	//������:�f�o�C�X
	//�߂�l  :�C���X�^���X�̃|�C���^
	static CPlayer* Create(LPDIRECT3DDEVICE9 device);

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

	//�L�[�{�[�h���̃Z�b�g
	void SetKeyboard(CInputKeyboard* keyboard){m_keyboard = keyboard;}

	//�ړ����x�̎擾����
	D3DXVECTOR2 move_spd_()
	{
		return (m_move_spd);
	}

private:
	//�L�[�{�[�h���i�[�ϐ�
	CInputKeyboard*	m_keyboard;
	//�v���C���[�̈ړ����x
	D3DXVECTOR2 m_move_spd;
	//�W�����v�����ǂ���
	bool isJump;
	//�W�����v�\���ǂ���
	bool canJump;
	//�U�������ǂ���
	bool isAttack;
	//���݂̃A�j���[�V�����ԍ�
	int nowAnim;
	//�A�j���[�V�����̃J�E���g�p
	int cntAnim;

	CScene2D* Assy;


	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		m_keyboard=NULL;
		Assy=NULL;
		cntAnim=0;
		nowAnim=1;
		m_move_spd=D3DXVECTOR2(0.0f,0.0f);
		isJump=false;
		isAttack=false;
		canJump=true;
	}
	//�ړ�����
	void Move();
	//�U������
	void Attack();
	//�W�����v����
	void moveJump();
	//�d�͂�������
	void AddGravity();
	//�l�X�ȓ����蔻��
	void Collider();
	//�A�j���[�V��������
	void Anim(int maxTex,int nowTex);



};

#endif

