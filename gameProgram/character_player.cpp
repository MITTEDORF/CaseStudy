//*****************************************************************************
//
// �v���C���[����N���X [character_player.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_player.h"
#include "inputKeyboard.h"
#include "math_animation.h"
#include "player_config.h"

#include "game.h"
#include "debugproc.h"
#include "fade.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(LPDIRECT3DDEVICE9 device)
{
	
	Assy=CScene2D::Create(device,CImport::TEX_ASSY_ONE,POINT_CENTER);
	Assy->Init(device,CImport::TEX_ASSY_ONE,POINT_CENTER);

	//�e�̏�����
	CScene2D::Init(device,CImport::TEX_PLAYER_WAIT,POINT_CENTER);

	SetAnim(1,1,this);


	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CPlayer::Uninit(void)
{
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	//�t�F�[�h���ł͂Ȃ��Ƃ�
	if(CPhase::GetFade()->GetState() == CFade::FADESTATE_NONE)
	{

		m_posOld = m_pos;
		
		//�ړ�����
		Move();

		//�U������
		Attack();

	}

	//�d�͉��Z
	AddGravity();

	//�X�s�[�h���l���������W�̎Z�o
	m_pos+=m_move_spd;

	//�l�X�ȓ����蔻��
	Collider();

	//�A�b�V�[�̃|�W�V�������Z�b�g
	Assy->SetPos(m_pos);
	
	//���W�̍Čv�Z
	SetVertexPolygon();
	//�e�̍X�V
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CPlayer::Draw(void)
{
	//�e�̕`��
	CScene2D::Draw();
}
//=============================================================================
// ����
//=============================================================================
CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 device)
{
	CPlayer* scene = new CPlayer;
	scene->Init(device);

	return scene;
}
//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move()
{
	//�E�ړ�
	if(m_keyboard->GetPress(DIK_A))
	{
		m_move_spd.x-=MOVE_SPD;
	}

	//���ړ�
	if(m_keyboard->GetPress(DIK_D))
	{
		m_move_spd.x+=MOVE_SPD;
	}

	//����
	m_move_spd.x*=MOVE_FRICTIONAL_FORCE;

	//�W�����v����
	moveJump();
}
//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::moveJump()
{
	//�X�y�[�X�L�[���������Ƃ�
	if(m_keyboard->GetTrigger(DIK_SPACE)&&canJump)
	{
		if(!isJump)
		{
			canJump=false;
			isJump=true;
			//�X�s�[�h�̐ݒ�
			m_move_spd.y=JUMP_SPD;
		}
	}
}
//=============================================================================
// �d�͉��Z����
//=============================================================================
void CPlayer::AddGravity()
{

	m_move_spd.y+=GRAVITY_SPD;

}
//=============================================================================
// �l�X�ȓ����蔻��
//=============================================================================
void CPlayer::Collider()
{
	//�n�ʂƃv���C���̓����蔻��
	if(m_pos.y>=625.0f)
	{
		canJump=true;
		isJump=false;
		m_pos.y=625.0f;
	}

	if(m_pos.x<=0.0f)
	{
		m_pos.x=0.0f;
	}

	if(m_pos.x>=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2)))
	{
		m_pos.x=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2));
	}

}
//=============================================================================
// �U������
//=============================================================================
void CPlayer::Attack()
{
	

	if(m_keyboard->GetTrigger(DIK_K)&&!isAttack)
	{
		cntAnim=0;
		nowAnim=1;
		isAttack=true;
		this->SetTex(CImport::TEX_PLAY_ATTACK);
		SetAnim(5,1,this);
	}

	if(isAttack)
	{
		switch (cntAnim)
		{
			case ATTACK_ANIM_SPD:
				SetAnim(5,2,this);
				break;

			case ATTACK_ANIM_SPD*2:
				SetAnim(5,3,this);
				break;

			case ATTACK_ANIM_SPD*3:
				SetAnim(5,4,this);
				break;

			case ATTACK_ANIM_SPD*4:
				SetAnim(5,5,this);
				break;

			case ATTACK_ANIM_SPD*5:
				cntAnim=0;
				nowAnim=1;
				isAttack=false;
				this->SetTex(CImport::TEX_PLAYER_WAIT);
				SetAnim(1,1,this);
				return;
				break;
		}

		cntAnim++;
	}
}