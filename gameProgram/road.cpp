//=============================================================================
//
// Roadクラス [road.cpp]
// Author : Ken Matsuura
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "road.h"

#define ROAD_SIZE	(64.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CRoad::CRoad(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_next = NULL;
	m_prev = NULL;
}

//=============================================================================
// 生成
//=============================================================================
CRoad* CRoad::Create(LPDIRECT3DDEVICE9 device, ROAD_DATA data, POINT_TYPE pointType)
{
	CRoad* pointer = new CRoad;
	pointer->Init(device, (CImport::TEXTURES)(CImport::DIRT + data.type), pointType);
	// データを元に座標の変更
	pointer->SetSize(ROAD_SIZE, ROAD_SIZE);
	pointer->SetHitSize(D3DXVECTOR2(ROAD_SIZE, ROAD_SIZE));
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 64));
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRoad::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
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
void CRoad::Uninit(void)
{
	// 継承元の終了処理呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CRoad::Update(void)
{
	// 継承元の更新処理呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画
//=============================================================================
void CRoad::Draw(void)
{
	// 継承元の描画処理呼び出し
	CScene2D::Draw();

	// 当たり判定ボックスの描画
	//DrawHitBox();
}

//=============================================================================
// 押し返し処理
//=============================================================================
D3DXVECTOR2	CRoad::ReturnPush(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// 自分の4頂点と相手の4頂点を計算
	D3DXVECTOR2 self[4], target[4], temp, rtn, selfpos,tarpos;

	temp = (m_size - m_hitSize)/2;

	// 自分の頂点情報を計算
	if(m_pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		self[0].x = m_pos.x + m_hitOffset.x + temp.x;				self[0].y = m_pos.y + m_hitOffset.y + temp.y;
		self[1].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = m_pos.y + m_hitOffset.y + temp.y;
		self[2].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		self[3].x = m_pos.x + m_hitOffset.x + temp.x;				self[3].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		selfpos.x = self[0].x + (self[1].x - self[0].x)/2;
		selfpos.y = self[0].y +(self[3].y - self[0].y)/2;
	}
	else if(m_pointType == POINT_CENTER)	// 中心原点の場合
	{
		self[0].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[1].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[2].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		self[3].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		selfpos = m_pos;
	}

	// 渡された情報から頂点を計算
	if(pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
		tarpos.x = target[0].x + (target[1].x - target[0].x)/2;
		tarpos.y = target[0].y + (target[3].y - target[0].y)/2;
	}
	else if(pointType == POINT_CENTER)	// 中心原点の場合
	{
		target[0].x = pos.x - size.x/2;		target[0].y = pos.y - size.y/2;
		target[1].x = pos.x + size.x/2;		target[1].y = pos.y - size.y/2;
		target[2].x = pos.x + size.x/2;		target[2].y = pos.y + size.y/2;
		target[3].x = pos.x - size.x/2;		target[3].y = pos.y + size.y/2;
		tarpos = pos;
	}

	rtn = D3DXVECTOR2(0.0f, 0.0f);

	//-------------------------------
	// めり込みチェック
	//-------------------------------
	// 上からめり込んできてる時
	//if(self[0].y > target[0].y && self[0].y < target[3].y && self[3].y > target[3].y && self[3].y > target[3].y)
	//	rtn.y = self[0].y - target[3].y;
	//// 上下ともにめり込んでる時
	//if(self[0].y > target[0].y && self[0].y < target[3].y && self[3].y > target[3].y && self[3].y < target[3].y)
	//	// 浅くめり込んでる方に押し返す
	//	if((self[0].y - target[0].y) < (target[3].y - self[3].y))
	//		rtn.y = target[3].y - self[0].y;
	//	else
	//		rtn.y = target[0].y - self[3].y;
	//// 下からめり込んできてる時
	//if(self[0].y < target[0].y && self[0].y < target[3].y && self[3].y > target[3].y && self[3].y < target[3].y)
	//	rtn.y = self[3].y - target[0].y;

	//// 左からめり込んできてる時
	//if(self[0].x > target[0].x && self[0].x < target[1].x && self[1].x > target[1].x && self[1].x > target[1].x)
	//	rtn.x = self[0].x - target[1].x;
	//// 左右ともにめり込んでる時
	//if(self[0].x > target[0].x && self[0].x < target[1].x && self[1].x > target[1].x && self[1].x < target[1].x)
	//	// 浅くめり込んでる方に押し返す
	//	if((self[0].x - target[0].x) < (target[1].x - self[1].x))
	//		rtn.x = target[1].x - self[0].x;
	//	else
	//		rtn.x = target[0].x - self[1].x;
	//// 右からめり込んできてる時
	//if(self[0].x < target[0].x && self[0].x < target[1].x && self[1].x > target[1].x && self[1].x < target[1].x)
	//	rtn.x = self[1].x - target[0].x;

	// 当たった？
	if (tarpos.x + (size.x / 2.0f) > selfpos.x - (m_hitSize.x / 2.0f) &&
		tarpos.x - (size.x / 2.0f) < selfpos.x + (m_hitSize.x / 2.0f))
	{
		if (tarpos.y + (size.y / 2.0f) > selfpos.y - (m_hitSize.y / 2.0f) &&
			tarpos.y - (size.y / 2.0f) < selfpos.y + (m_hitSize.y / 2.0f))
		{
			// 当たった上で、どこから？
			// 上下どっちからか
			if (tarpos.y > selfpos.y)
			{
				// 下
				
				// 左右どっちからか
				if (tarpos.x > selfpos.x)
				{
					// 右
					D3DXVECTOR2 vec(
						(tarpos.x - (size.x / 2.0f)) - (selfpos.x + (m_hitSize.x / 2.0f)),
						(tarpos.y - (size.y / 2.0f)) - (selfpos.y + (m_hitSize.y / 2.0f)));
					// X成分とY成分を比較
					if ((vec.x * vec.x) > (vec.y * vec.y))
					{
						tarpos.y -= vec.y;
					}
					else
					{
						tarpos.x -= vec.x;
					}
				}
				else
				{
					// 左
					D3DXVECTOR2 vec(
						(tarpos.x + (size.x / 2.0f)) - (selfpos.x - (m_hitSize.x / 2.0f)),
						(tarpos.y - (size.y / 2.0f)) - (selfpos.y + (m_hitSize.y / 2.0f)));
					// X成分とY成分を比較
					if ((vec.x * vec.x) > (vec.y * vec.y))
					{
						// 横のほうが長いから、上に行こう
						tarpos.y -= vec.y;
					}
					else
					{
						// 縦の方が長いから、横に行こう
						tarpos.x -= vec.x;
					}
				}
			}
			else
			{
				// 上

				// 左右どっちからか
				if (tarpos.x > selfpos.x)
				{
					// 右
					D3DXVECTOR2 vec(
						(tarpos.x - (size.x / 2.0f)) - (selfpos.x + (m_hitSize.x / 2.0f)),
						(tarpos.y + (size.y / 2.0f)) - (selfpos.y - (m_hitSize.y / 2.0f)));
					// X成分とY成分を比較
					if ((vec.x * vec.x) > (vec.y * vec.y))
					{
						// 横のほうが長いから、上に行こう
						tarpos.y -= vec.y;
					}
					else
					{
						// 縦の方が長いから、横に行こう
						tarpos.x -= vec.x;
					}
				}
				else
				{
					// 左
					D3DXVECTOR2 vec(
						(tarpos.x + (size.x / 2.0f)) - (selfpos.x - (m_hitSize.x / 2.0f)),
						(tarpos.y + (size.y / 2.0f)) - (selfpos.y - (m_hitSize.y / 2.0f)));
					// X成分とY成分を比較
					if ((vec.x * vec.x) > (vec.y * vec.y))
					{
						// 横のほうが長いから、上に行こう
						tarpos.y -= vec.y;
					}
					else
					{
						// 縦の方が長いから、横に行こう
						tarpos.x -= vec.x;
					}
				}
			}
		}
	}
	rtn = tarpos - pos;
	return rtn;
}

// End of File