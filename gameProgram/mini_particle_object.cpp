//*****************************************************************************
//
// �p�[�e�B�N������N���X [particle_object.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "particle_manager.h"
#include "import.h"

#include <math.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMiniParticleObject::CMiniParticleObject(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMiniParticleObject::Init(LPDIRECT3DDEVICE9 device)
{
	//�e�̏�����
	CScene2D::Init(device,CImport::PARTICLE_YELLOW_SMALL,POINT_CENTER);
	

	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CMiniParticleObject::Uninit(void)
{
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CMiniParticleObject::Update(void)
{
	if(isUse)
	{
		ColA-=0.05f;
		m_Rad+=D3DX_PI*0.05f;

		if(m_Rad>D3DX_PI)
		{
			m_Rad-=D3DX_PI*2.0f;
		}

		m_color.a=ColA;
		m_color.r=sinf(m_Rad)+1.5f;
		m_color.g=sinf(m_Rad+(D3DX_PI*0.666f))+1.5f;
		m_color.b=sinf(m_Rad+(D3DX_PI*1.333f))+1.5f;



		Angle+=Anglespd;

		SetColor(m_color);

		SetRot(Angle);
		//���W�̍Čv�Z
		SetVertexPolygon();

		//�e�̍X�V
		CScene2D::Update();

		if(ColA<=0)
		{
			Destroy();
		}
	}
}
//=============================================================================
// �`��
//=============================================================================
void CMiniParticleObject::Draw(void)
{
	if(isUse)
	{
		//�e�̕`��
		CScene2D::Draw();
	}
}
//=============================================================================
// ����
//=============================================================================
CMiniParticleObject* CMiniParticleObject::Create(LPDIRECT3DDEVICE9 device)
{
	CMiniParticleObject* scene = new CMiniParticleObject;
	scene->Init(device);

	return scene;
}

//=============================================================================
// �p�[�e�B�N���J�n����
//=============================================================================
void CMiniParticleObject::Start(D3DXVECTOR2 pos)
{
		int dsize=2 + (int)( rand() * (5 - 2 + 1.0) / (1.0 + RAND_MAX) );
		SetSize((128.0f*1.5f*0.2f),(128.0f*1.5f*0.2f));

		isUse = true;

		this->SetPos(pos.x,pos.y);

		this->SetTex(CImport::PARTICLE_WHITE_SMALL);

		ColA=1.0f;

		Angle=0.0f;

		Anglespd=(float)(0.01 + (int)( rand() * (0.2 - 0.01 + 1.0)) / (float)(1.0 + RAND_MAX) );


		m_Rad=(float)(0 + (int)( rand() * (D3DX_PI - 0 + 1.0)) / (float)(1.0 + RAND_MAX) );
}

//=============================================================================
// �p�[�e�B�N���j�󏈗�
//=============================================================================
void CMiniParticleObject::Destroy()
{
	isUse=false;
}