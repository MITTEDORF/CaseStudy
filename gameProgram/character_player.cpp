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

#include "game.h"
#include "debugproc.h"
#include "fade.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const float JUMP_SPD    = -40.0f;
const float MOVE_SPD    = 3.0f;
const float GRAVITY_SPD = 2.0f;

float MapValues(float x,float inMin,float inMax,float outMin,float outMax);

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

	Anim(1,1);


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
	m_move_spd.x*=0.8f;

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
}
//=============================================================================
// �A�j���[�V��������
//=============================================================================
void CPlayer::Anim(int maxTex,int nowTex)
{
	
	float uvOffset;
	uvOffset=MapValues(1.0f,0,(float)maxTex,0,1.0f);

	D3DXVECTOR2 cord=D3DXVECTOR2(uvOffset*(float)(nowTex-1),0);
	this->SetCord(0,cord);

	cord=D3DXVECTOR2(uvOffset*(float)(nowTex),0);
	this->SetCord(1,cord);

	cord=D3DXVECTOR2(uvOffset*(float)(nowTex-1),1.0f);
	this->SetCord(2,cord);

	cord=D3DXVECTOR2(uvOffset*(float)(nowTex),1.0f);
	this->SetCord(3,cord);

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
		Anim(5,1);
	}

	if(isAttack)
	{
		switch (cntAnim)
		{
			case 10:
				Anim(5,2);
				break;

			case 10*2:
				Anim(5,3);
				break;

			case 10*3:
				Anim(5,4);
				break;

			case 10*4:
				Anim(5,5);
				break;

			case 10*5:
				cntAnim=0;
				nowAnim=1;
				isAttack=false;
				this->SetTex(CImport::TEX_PLAYER_WAIT);
				Anim(1,1);
				return;
				break;
		}

		cntAnim++;
	}
}

//=============================================================================
// �ő�l�A�ŏ��l���l���������ݒl�̎Z�o
//=============================================================================
float MapValues(float x,float inMin,float inMax,float outMin,float outMax)
{
	return ((x-inMin)*(outMax-outMin)/(inMax-inMin)+outMin);
}