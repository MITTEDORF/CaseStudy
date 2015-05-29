//*****************************************************************************
//
// goalクラス [goal.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "goal.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal( int priority , OBJTYPE objtype ) : CScene2D( priority , objtype )
{
}
//=============================================================================
// 生成
//=============================================================================
CGoal* CGoal::Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CGoal* pointer = new CGoal( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	return pointer;
}

CGoal* CGoal::Create(LPDIRECT3DDEVICE9 device, const char* texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CGoal* pointer = new CGoal( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	return pointer;
}
//=============================================================================
// 初期化
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
// 終了
//=============================================================================
void CGoal::Uninit( void )
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CGoal::Update( void )
{
	//当たり判定

	{
		m_Goal = TRUE;
	}
	{
		m_Goal = FALSE;
	}
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CGoal::Draw( void )
{
	CScene2D::Draw();
}