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
	if( m_Flag == TRUE )
	{
		this->SetTex( CImport::GOAL_ON );
	}
	//当たり判定
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CGoal::Draw( void )
{
	CScene2D::Draw();

	// 当たり判定ボックスの描画
	DrawHitBox();
}

//=============================================================================
// スクロール処理
//=============================================================================
void CGoal::Scroll( float scroll )
{
	m_pos.x -=scroll;
	CScene2D::SetVertexPolygon();
}
