//*****************************************************************************
//
// ��蕨����N���X [character_vehicle.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_vehicle.h"
#include "vehicle_config.h"

#include "character_player.h"
#include "math_animation.h"

#include "game.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVehicle::CVehicle(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CVehicle::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture)
{
	//�e�̏�����
	CScene2D::Init(device,texture,POINT_CENTER);

	//�A�j���[�V�����̏�����
	SetAnimMode(VEHICLE_ANIM_WAIT,true);

	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CVehicle::Uninit(void)
{
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CVehicle::Update(void)
{
	UpdateAnim();

	//���W�̍Čv�Z
	SetVertexPolygon();
	//�e�̍X�V
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CVehicle::Draw(void)
{
	//�e�̕`��
	CScene2D::Draw();
}
//=============================================================================
// ����
//=============================================================================
CVehicle* CVehicle::Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture)
{
	CVehicle* scene = new CVehicle;
	scene->Init(device,texture);

	return scene;
}

//=============================================================================
//�A�j���[�V�����̍X�V����
//=============================================================================
void CVehicle::UpdateAnim()
{
	switch(AnimMode)
	{
	case VEHICLE_ANIM_WAIT:

		break;

	case VEHICLE_ANIM_MOVE:

		break;

	case VEHICLE_ANIM_ATACK:
		
		break;

	case VEHICLE_ANIM_DAMAGE:
		break;
	}

	if(isAnimEnd)
	{
		if(isRupeAnim)
		{
			cntAnim=0;
			nowAnim=1;
			SetAnim(maxAnim,1,this);
		}

		else
		{
			SetAnimMode(VEHICLE_ANIM_WAIT,true);
		}

		isAnimEnd=false;
	}
}
//=============================================================================
//�A�j���[�V�����̃Z�b�g����
//=============================================================================
void CVehicle::SetAnimMode(int AnimID,bool Rupe)
{
	if(AnimMode==AnimID)
	{
		return;
	}

	switch (AnimID)
	{
	case VEHICLE_ANIM_WAIT:
		cntAnim=0;
		nowAnim=1;
		maxAnim=1;
		this->SetTex(CImport::TEX_ASSY_ONE);
		SetAnim(maxAnim,1,this);
		break;

	case VEHICLE_ANIM_MOVE:

		break;

	case VEHICLE_ANIM_ATACK:
		cntAnim=0;
		nowAnim=1;
		maxAnim=5;
		this->SetTex(CImport::TEX_PLAY_ATTACK);
		SetAnim(maxAnim,1,this);
		break;

	case VEHICLE_ANIM_DAMAGE:

		break;
	}

	AnimMode=AnimID;
	isRupeAnim=Rupe;

}

