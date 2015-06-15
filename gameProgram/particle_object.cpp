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
#include "particle_object.h"
#include "import.h"

#include <math.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticleObject::CParticleObject(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticleObject::Init(LPDIRECT3DDEVICE9 device)
{
	//�e�̏�����
	CScene2D::Init(device,CImport::PARTICLE_YELLOW_SMALL,POINT_CENTER);
	

	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CParticleObject::Uninit(void)
{
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CParticleObject::Update(void)
{
	float dt = 0.01f;

	//�J�E���g�A�b�v
	if( m_Laser.Use )
	{
		m_Laser.Time += dt;

		if( (m_Laser.Time > 1.0f) )
		{
			m_Laser.Use = false;
		}

		Angle+=0.2f;
	}

	if( m_Laser.Use == true )
	{
		float t;
		float h00, h01, h10, h11;

		t = m_Laser.Time;

		h00 = (t-1.0f) *(t-1.0f) *(2.0f*t+1.0f);
		h01 = t*t*(3.0f-2.0f*t) ;
		h10 = (1.0f-t)*(1.0f-t)*t;
		h11 = t*t*(t-1.0f);

		if(objtarget==this)
		{
			m_pos.x = h00 *m_Laser.Position.x +
				h01 *objtarget->GetPos().x +
				h10 * m_Laser.ControlVector0.x +
				h11 * m_Laser.ControlVector1.x;

			m_pos.y = h00 * m_Laser.Position.y +
				h01 * objtarget->GetPos().y +
				h10 * m_Laser.ControlVector0.y +
				h11 * m_Laser.ControlVector1.y;
		}

		else
		{
			m_pos.x = h00 *m_Laser.Position.x+
				h01 *objtarget->GetPos().x+(objtarget->GetSize().x/2) +
				h10 * m_Laser.ControlVector0.x +
				h11 * m_Laser.ControlVector1.x;

			m_pos.y = h00 * m_Laser.Position.y +
				h01 * objtarget->GetPos().y+(objtarget->GetSize().y/2) +
				h10 * m_Laser.ControlVector0.y +
				h11 * m_Laser.ControlVector1.y;
		}
	}
		SetRot(Angle);
		//���W�̍Čv�Z
		SetVertexPolygon();

		//�e�̍X�V
		CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CParticleObject::Draw(void)
{
	if(m_Laser.Use)
	{
		//�e�̕`��
		CScene2D::Draw();
	}
}
//=============================================================================
// ����
//=============================================================================
CParticleObject* CParticleObject::Create(LPDIRECT3DDEVICE9 device)
{
	CParticleObject* scene = new CParticleObject;
	scene->Init(device);

	return scene;
}

//=============================================================================
// �p�[�e�B�N���J�n����
//=============================================================================
void CParticleObject::Start(D3DXVECTOR2 pos,CScene *target)
{
	if(!m_Laser.Use)
	{
		m_Laser.Time = 0.0f;

		m_pos.x=m_Laser.Position.x= pos.x;
		m_pos.y=m_Laser.Position.y= pos.y;


		if(target)
		{
			objtarget=target;
			m_Laser.Position.x = pos.x-(objtarget->GetSize().x/2);
			m_Laser.Position.y = pos.y-(objtarget->GetSize().y/2);

		}

		else
		{
			objtarget=this;
		}

		m_Laser.ControlVector0.x = (float)(rand() % 6000 - 3000);
		m_Laser.ControlVector0.y = (float)(rand() % 6000 - 3000);
		m_Laser.ControlVector1.x = (float)(rand() % 6000 - 3000);
		m_Laser.ControlVector1.y = (float)(rand() % 6000 - 3000);
		int dsize=2 + (int)( rand() * (5 - 2 + 1.0) / (1.0 + RAND_MAX) );
		SetSize((128.0f*dsize*0.2f),(128.0f*dsize*0.2f));
		m_Laser.Use = true;
		int tex=1 + (int)( rand() * (3 - 1 + 1.0) / (1.0 + RAND_MAX) );
		switch (tex)
		{
		case 1:
			this->SetTex(CImport::PARTICLE_YELLOW_SMALL);
			break;
		case 2:
			this->SetTex(CImport::PARTICLE_DAIDAI_SMALL);
			break;
		case 3:
			this->SetTex(CImport::PARTICLE_WHITE_SMALL);
			break;
		}
	}
}

//=============================================================================
// �p�[�e�B�N���j�󏈗�
//=============================================================================
void CParticleObject::Destroy()
{
	m_Laser.Use=false;
}