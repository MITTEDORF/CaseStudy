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
	//当たり判定
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CGoal::Draw( void )
{
	CScene2D::Draw();
}
//=============================================================================
// 衝突判定 (渡された情報と自分の情報を比較する(松浦式流用)
//=============================================================================
BOOL CGoal::CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// 自分の4頂点と相手の4頂点を計算
	D3DXVECTOR2 self[4], target[4];

	// 自分の頂点情報を計算
	if(m_pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		self[0].x = m_pos.x;				self[0].y = m_pos.y;
		self[1].x = m_pos.x + m_size.x;		self[1].y = m_pos.y;
		self[2].x = m_pos.x + m_size.x;		self[2].y = m_pos.y + m_size.y;
		self[3].x = m_pos.x;				self[3].y = m_pos.y + m_size.y;
	}
	else if(m_pointType == POINT_CENTER)	// 中心原点の場合
	{
		self[0].x = m_pos.x - m_size.x/2;	self[0].y = m_pos.y - m_size.y/2;
		self[1].x = m_pos.x + m_size.x/2;	self[1].y = m_pos.y - m_size.y/2;
		self[2].x = m_pos.x + m_size.x/2;	self[2].y = m_pos.y + m_size.y/2;
		self[3].x = m_pos.x - m_size.x/2;	self[3].y = m_pos.y + m_size.y/2;
	}

	// 渡された情報から頂点を計算
	if(m_pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
	}
	else if(m_pointType == POINT_CENTER)	// 中心原点の場合
	{
		target[0].x = pos.x - size.x/2;		target[0].y = pos.y - size.y/2;
		target[1].x = pos.x + size.x/2;		target[1].y = pos.y - size.y/2;
		target[2].x = pos.x + size.x/2;		target[2].y = pos.y + size.y/2;
		target[3].x = pos.x - size.x/2;		target[3].y = pos.y + size.y/2;
	}

	// AABB衝突判定
	if( (self[0].x < target[1].x) &&
		(target[0].x < self[1].x) &&
		(self[0].y < target[3].y) &&
		(target[0].y < self[3].y) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//=============================================================================
// スクロール処理
//=============================================================================
void CGoal::Scroll( float scroll )
{
	m_pos.x -=scroll;
	CScene2D::SetVertexPolygon();
}
