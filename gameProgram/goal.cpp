//*****************************************************************************
//
// goal�N���X [goal.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "goal.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal::CGoal( int priority , OBJTYPE objtype ) : CScene2D( priority , objtype )
{
}
//=============================================================================
// ����
//=============================================================================
CGoal* CGoal::Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CGoal* pointer = new CGoal( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	pointer->SetHitSize(D3DXVECTOR2(32, SCREEN_HEIGHT));
	pointer->SetHitOffset(D3DXVECTOR2(0.0f, -232.0f));
	pointer->SetGoal( pointer );
	return pointer;
}

CGoal* CGoal::Create(LPDIRECT3DDEVICE9 device, const char* texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CGoal* pointer = new CGoal( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	pointer->SetGoal( pointer );
	return pointer;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CGoal::Init( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType )
{
	CScene2D::Init( device , texture , pointType );
	return S_OK;
}

HRESULT	CGoal::Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
{
	CScene2D::Init( device , texture , pointType );
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGoal::Uninit( void )
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CGoal::Update( void )
{
	if( m_Flag == TRUE )
	{
		this->SetTex( CImport::GOAL_ON );
	}
	//�����蔻��
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CGoal::Draw( void )
{
	CScene2D::Draw();

	// �����蔻��{�b�N�X�̕`��
	DrawHitBox();
}

//=============================================================================
// �X�N���[������
//=============================================================================
void CGoal::Scroll( float scroll )
{
	m_pos.x -=scroll;
	CScene2D::SetVertexPolygon();
}
