//*****************************************************************************
//
// stumblerクラス [stumbler.cpp]
// Author : KEN MATSUURA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stumbler.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CStumbler::CStumbler(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_life = 1;
}

//=============================================================================
// 生成
//=============================================================================
CStumbler* CStumbler::Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType)
{
	CStumbler* pointer = new CStumbler;
	pointer->Init(device, (CImport::TEXTURES)(CImport::SIGNBOARD + data.type), pointType);
	// データを元に座標の変更
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStumbler::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
{
	HRESULT hr;

	// 継承元の初期化呼び出し
	hr = CScene2D::Init(device, texture, pointType);
	// 継承元の初期化に失敗したら
	if(hr == E_FAIL)
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CStumbler::Uninit(void)
{
	// 継承元の終了処理呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CStumbler::Update(void)
{
	// 継承元の更新処理呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画
//=============================================================================
void CStumbler::Draw(void)
{
	// 継承元の描画処理呼び出し
	CScene2D::Draw();
}

//=============================================================================
// 障害物の生存チェック
//=============================================================================
bool CStumbler::LivingCheck(void)
{
	if(m_life <= 0)
	{
		return true;
	}
	return false;
}

//=============================================================================
// 衝突判定 (渡された情報と自分の情報を比較する
//=============================================================================
bool CStumbler::CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
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
		return true;
	}
	else
	{
		return false;
	}
}