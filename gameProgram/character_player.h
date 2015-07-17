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
#include "character_config.h"
#include "player_config.h"

#include "character_vehicle.h"
//=============================================================================
// �}�N��
//============================================================================

//=============================================================================
// �O���錾
//=============================================================================
//�L�[�{�[�h���͐���N���X
class CInputKeyboard;
class CInputPadX;
class CParticleManager;
class CSound;
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
	static CPlayer* Create(LPDIRECT3DDEVICE9 device,CostumeID costume_id=COSTUME_NONE,VehicleID vehicle_id=(VehicleID)0);

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
	//�p�b�h���̃Z�b�g
	void SetPadX(CInputPadX* padX){m_padX = padX;}

	//�ړ����x�̎擾����
	//�߂�l:�v���C���[�̈ړ���
	D3DXVECTOR2 move_spd_()
	{
		return (m_move_spd);
	}

	//HP�̎擾����
	//�߂�l:�v���C���[��HP
	int HP_()
	{
		return (HP);
	}

	//�v���C���[�̐����m�F
	//�߂�l:����ł���false���Ԃ��Ă����
	bool isDeth_()
	{
		return (isDeth);
	}

	//���G��Ԃ��ǂ����̎擾
	//�߂�l:���G��ԂȂ�true���Ԃ��Ă����
	bool isinvincible_()
	{
		return (isinvincible);
	}

	//�p�[�e�B�N���Ǘ��N���X�̎擾
	//�߂�l:�p�[�e�B�N���Ǘ��N���X�̃|�C���^
	CParticleManager* particle_()
	{
		return (particle);
	}

	//���A�N�V���������ǂ����̃`�F�b�N
	//�߂�l:true�Ȃ���A�N�V����������
	bool isLitninng()
	{
		return(isAnimEnd&&isHoldLighting);
	}

	//�p�[�e�B�N������o
	//������:�p�[�e�B�N�����������ڕW�̃|�C���^(NULL�������΂ق�`���Ə�����)
	void PaticleStart(CScene* target);
	//�p�[�e�B�N���̉�ʃX�N���[������(�Ƃ肠�������t���[���Ă��)
	//������:�X�N���[���̒l
	void ParticleScrol(float value);

	//HP�̉��Z����
	//������:���Z����l(���Z�������ꍇ��-�̒l�����Ă�������)
	void AddHP(int value);

	//�R�X�`���[���̃Z�b�g
	//������:ID����Ă�(character_config�ɂĒ�`)
	void SetCostumeID(CostumeID value);

	//��蕨�̃Z�b�g
	//������:ID����Ă�(character_config�ɂĒ�`)
	void SetVehicleID(VehicleID value);
	
	//���݂̃V�[�����Q�[�������ǂ����؂�ւ���
	//������:�Q�[�����Ȃ�true�A����ȊO��false
	void Set_isGame(bool value);

	//�v���C���[�̒l�����t���b�V������
	//������:���ɍۂɏ��W�����v�����������ꍇ��true������
	void PlayerReflash(bool value=true)
	{
		isLighting=false;
		if(value||isFall)
		{
			m_move_spd.y=0.0f;
		}

		else
		{
			m_move_spd.y=JUMP_SPD/1.5f;
		}
	}

	void PlayerGoal()
	{
		isLighting=false;
		isGoal=true;
		SetAnimMode(PLAYER_ANIM_LIGHT,false);
		m_move_spd.y=0.0f;
		m_move_spd.x=MOVE_FRICTIONAL_FORCE*50.0f;
	}

	
	//�A�b�V�[�̃|�C���^��n��
	//�߂�l:�A�b�V�[�̃|�C���^�[
	CVehicle* Assy_()
	{
		return (Assy);
	}
	
	//�����ݒn�ʂɒ��n�����ǂ������ׂ�
	//�߂�l:�n�ʂɒ��n���Ȃ��true���Ԃ��Ă���
	bool isGround_()
	{
		return (isGround);
	}

	//�����ݒn�ʂɒ��n�����ǂ������Z�b�g�o����(�ڒn����ȊO�ł͌ĂԂ�NG)
	//������:���n���Ȃ��true������
	void isGround_set(bool value)
	{
		if(isGround==value){return;}
		isGround=value;
	}

	//Y�����̍�����0�ɂ���
	void SpdKill()
	{
		m_move_spd.y=0.0f;
	}

	//�W�����v�\��Ԃɂ���
	void SetCanJump()
	{
		isJump=false;
		canJump=true;
	}

	bool isFadeStart_()
	{
		return (isFadeStart);
	}

	void SetSound(CSound* psound)
	{
		sound=psound;
	}
	
	//�e�N�X�`��ID�̎Q��
	CImport::TEXTURES ConsultationPlayerTexID(PlayerState state,int offset=0);
	CImport::TEXTURES ConsultationVehicleTexID(int offset=0);

private:
	void DrawHitBox(void);

	CSound * sound;

	//�e�N�X�`��ID
	CostumeID Costume_id;
	VehicleID Vehicle_id;

	//�Q�[�������ǂ���
	bool isGame;
	//���n�ʂɐڒn���Ă��邩�ǂ���
	bool isGround;
	//�`��t���O
	bool isDraw;
	//�����Ă��邩�ǂ���
	bool isFall;
	//�W�����v�����ǂ���
	bool isJump;
	//�W�����v�\���ǂ���
	bool canJump;
	//�U�������ǂ���
	bool isAttack;
	//���A�N�V���������ǂ���
	bool isLighting;
	//���A�N�V�������p�����邩�ǂ���
	bool isHoldLighting;
	//���A�N�V�������\���ǂ���
	bool canLighting;
	//�u�]�t���O
	bool isDeth;
	//���G�t���O
	bool isinvincible;
	//�A�j���[�V�����̃��[�v�t���O
	bool isRupeAnim;
	//�A�j���[�V������1���I���t���O
	bool isAnimEnd;
	//�S�[�������ǂ����̃t���O
	bool isGoal;
	//�o�[�X�g�������t���O
	bool isBurst;

	bool isFadeStart;

	//�p�[�e�B�N���Ǘ��N���X
	CParticleManager *particle;
	//�L�[�{�[�h���i�[�ϐ�
	CInputKeyboard* m_keyboard;
	//�p�b�h���i�[�ϐ�
	CInputPadX* m_padX;
	//�A�b�V�[�Ǘ��N���X
	CVehicle* Assy;

	//�v���C���[�̈ړ����x
	D3DXVECTOR2 m_move_spd;
	//Y�l�I�t�Z�b�g
	D3DXVECTOR2 Offset;

	//�v���C���[��HP
	int HP;
	//�r�[�N���_���[�W�l
	int AssyDamage;
	//�r�[�N���̑ϋv(1�`3)
	int AssyHP;
	//���G�J�E���^�[
	int isinvincibleCnt;
	//���G�̌����ڃJ�E���^�[
	int isinvincibleDrawCnt;

	//���݂̃A�j���[�V�������[�h
	int AnimMode;
	//���݂̃A�j���[�V�����ԍ�
	int nowAnim;
	//�A�j���[�V�����̃J�E���g�p
	int cntAnim;
	//�A�j���[�V�����̍ő�R�}��
	int maxAnim;

	//���G����
	float InbisibleTime;
	//�ړ����x
	float MoveSpd;
	//�W�����v��
	float JumpSpd;

	//�d�͒l
	float localGravity;

	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		isFadeStart=false;
		isBurst=false;
		isGoal=false;
		particle=NULL;
		isGround=false;
		Offset.x=0;
		Offset.y=0;
		isGame=true;
		HP=PLAYER_HP_MAX;
		AssyDamage=HP/3;
		AssyHP=PLAYER_HP_MAX;
		isinvincible=false;
		isDraw=true;
		isDeth=false;
		isFall=false;
		InbisibleTime=INVISIBLE_TIME;
		isinvincibleDrawCnt=0;
		maxAnim=1;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=-1;
		m_keyboard=NULL;
		m_padX=NULL;
		Assy=NULL;
		cntAnim=0;
		nowAnim=1;
		m_move_spd=D3DXVECTOR2(0.0f,0.0f);
		isJump=false;
		canJump=true;
		isAttack=false;
		isLighting=false;
		isHoldLighting=false;
		canLighting=true;
		isinvincibleCnt=0;
		localGravity=GRAVITY_SPD;
		MoveSpd=MOVE_SPD;
		JumpSpd=JUMP_SPD;
	}

	//�ړ�����
	void Move();
	//�U������
	void Attack();
	//�W�����v����
	void moveJump();
	//���A�N�V��������
	void LightAction();
	//�d�͂�������
	void AddGravity();
	//�l�X�ȓ����蔻��
	void Collider();
	//�A�j���[�V�����̍X�V����
	void UpdateAnim();
	//�A�j���[�V�����̃Z�b�g����
	void SetAnimMode(int animID,bool Rupe);
	//HP�̍X�V
	void HPUpdate();
	//���G����
	void InvincibleUpdate();
};

#endif

