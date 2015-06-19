//*****************************************************************************
//
// CScene2Dクラス [scene2D.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define POLIGON_SIZE (128.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int priority, OBJTYPE objType) : CScene(priority, objType)
{
	m_localTex	= false;
	m_texture	= NULL;
	m_vtxBuff	= NULL;

	m_rot	= 0.0f;
	m_pos	= D3DXVECTOR2(0.0f, 0.0f);
	m_size	= D3DXVECTOR2(POLIGON_SIZE, POLIGON_SIZE);
	m_color	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR2 half = D3DXVECTOR2(m_size.x / 2.0f, m_size.y / 2.0f);
	m_length = DISTANCE_2D(half.x, half.y);
	m_angle	 = atan2f(half.x, half.y);

	m_coord[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_coord[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_coord[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_coord[3] = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// 生成
//=============================================================================
CScene2D* CScene2D::Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType, int priority)
{
	CScene2D* pointer = new CScene2D(priority);
	pointer->Init(device, texture, pointType);
	return pointer;
}

CScene2D* CScene2D::Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
{
	CScene2D* pointer = new CScene2D;
	pointer->Init(device, texture, pointType);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CScene2D::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
{
	//----------------------------
	// デバイス取得
	//----------------------------
	m_device = device;

	//----------------------------
	// ポイントのタイプ取得
	//----------------------------
	m_pointType = pointType;

	//----------------------------
	// ポリゴン初期化
	//----------------------------
	// メモリ確保
	HRESULT_FUNC(m_device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
											  D3DUSAGE_WRITEONLY,
											  FVF_VERTEX_2D,
											  D3DPOOL_MANAGED,
											  &m_vtxBuff,
											  NULL))

	// 頂点情報設定
	SetVertexPolygon();

	// テクスチャ取得
	m_texture = CImport::GetTexture(texture);
	m_localTex = false;

	// 当たり判定サイズ
	m_hitSize = m_size;

	// 当たり判定用座標
	m_hitPos = m_pos;

	// 当たり判定座標オフセット
	m_hitOffset = D3DXVECTOR2(0.0f, 0.0f);

	return S_OK;
}

HRESULT CScene2D::Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
{
	//----------------------------
	// デバイス取得
	//----------------------------
	m_device = device;

	//----------------------------
	// ポイントのタイプ取得
	//----------------------------
	m_pointType = pointType;

	//----------------------------
	// ポリゴン初期化
	//----------------------------
	// メモリ確保
	HRESULT_FUNC(m_device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
											  D3DUSAGE_WRITEONLY,
											  FVF_VERTEX_2D,			// 頂点フォーマット
											  D3DPOOL_MANAGED,
											  &m_vtxBuff,				// 頂点情報
											  NULL))

	// 頂点情報設定
	SetVertexPolygon();

	// テクスチャ取得
	D3DXCreateTextureFromFile(device, texture, &m_texture);
	m_localTex = true;
	
	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CScene2D::Uninit(void)
{
	if(m_localTex)
	{
		SAFE_RELEASE(m_texture);
	}

	// 頂点バッファの開放
	SAFE_RELEASE(m_vtxBuff);

	// 開放
	CScene::Delete();
}

//=============================================================================
// 更新
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// 描画
//=============================================================================
void CScene2D::Draw(void)
{
	//頂点バッファをデータストリームにバインド
	m_device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	m_device->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	m_device->SetTexture(0, m_texture);

	//描画設定
	m_device->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//描画種類
							0,						//
							2);						//ポリゴンの数
}

//=============================================================================
// 頂点情報設定
//=============================================================================
void CScene2D::SetVertexPolygon(void)
{
	VERTEX_2D* vtx;
	D3DXVECTOR2	work[4];

	// 座標設定
	switch(m_pointType)
	{
	case POINT_LEFTTOP:
		{
			// 各頂点の座標計算
			work[0].x = m_pos.x;
			work[0].y = m_pos.y;
			work[1].x = m_pos.x + m_size.x;
			work[1].y = m_pos.y;
			work[2].x = m_pos.x;
			work[2].y = m_pos.y + m_size.y;
			work[3].x = m_pos.x + m_size.x;
			work[3].y = m_pos.y + m_size.y;
			break;
		}

	case POINT_CENTER:
		{
			// 頂点距離・角度更新
			D3DXVECTOR2 half = D3DXVECTOR2(m_size.x / 2.0f, m_size.y / 2.0f);
			m_length = DISTANCE_2D(half.x, half.y);
			m_angle	 = atan2f(half.x, half.y);

			// 各頂点の座標計算
			work[0].x = m_pos.x - sinf(m_angle - m_rot) * m_length;
			work[0].y = m_pos.y - cosf(m_angle - m_rot) * m_length;
			work[1].x = m_pos.x + sinf(m_angle + m_rot) * m_length;
			work[1].y = m_pos.y - cosf(m_angle + m_rot) * m_length;
			work[2].x = m_pos.x - sinf(m_angle + m_rot) * m_length;
			work[2].y = m_pos.y + cosf(m_angle + m_rot) * m_length;
			work[3].x = m_pos.x + sinf(m_angle - m_rot) * m_length;
			work[3].y = m_pos.y + cosf(m_angle - m_rot) * m_length;
			break;
		}
	}

	// 開始
	m_vtxBuff->Lock(0, 0, (void **)&vtx, 0);

	// 座標
	vtx[0].vtx = D3DXVECTOR3(work[0].x, work[0].y, 0.0f);
	vtx[1].vtx = D3DXVECTOR3(work[1].x, work[1].y, 0.0f);
	vtx[2].vtx = D3DXVECTOR3(work[2].x, work[2].y, 0.0f);
	vtx[3].vtx = D3DXVECTOR3(work[3].x, work[3].y, 0.0f);

	// 1.0f固定
	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	// 反射光
	vtx[0].diffuse = m_color;
	vtx[1].diffuse = m_color;
	vtx[2].diffuse = m_color;
	vtx[3].diffuse = m_color;

	// テクスチャ座標
	vtx[0].tex = D3DXVECTOR2(m_coord[0].x, m_coord[0].y);
	vtx[1].tex = D3DXVECTOR2(m_coord[1].x, m_coord[1].y);
	vtx[2].tex = D3DXVECTOR2(m_coord[2].x, m_coord[2].y);
	vtx[3].tex = D3DXVECTOR2(m_coord[3].x, m_coord[3].y);

	// 終了
	m_vtxBuff->Unlock();
}

//=============================================================================
// 衝突判定 (渡された情報と自分の情報を比較する
//=============================================================================
bool CScene2D::CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// 自分の4頂点と相手の4頂点を計算
	D3DXVECTOR2 self[4], target[4], temp;

	temp = (m_size - m_hitSize)/2;

	// 自分の頂点情報を計算
	if(m_pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		self[0].x = m_pos.x + m_hitOffset.x + temp.x;				self[0].y = m_pos.y + m_hitOffset.y + temp.y;
		self[1].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = m_pos.y + m_hitOffset.y + temp.y;
		self[2].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		self[3].x = m_pos.x + m_hitOffset.x + temp.x;				self[3].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
	}
	else if(m_pointType == POINT_CENTER)	// 中心原点の場合
	{
		self[0].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[1].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[2].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		self[3].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
	}

	// 渡された情報から頂点を計算
	if(pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
	}
	else if(pointType == POINT_CENTER)	// 中心原点の場合
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

//=============================================================================
// 当たり判定ボックスの描画
//=============================================================================
void CScene2D::DrawHitBox(void)
{
	// 自分の頂点情報を計算
	D3DXVECTOR2 self[4], temp;

	temp = (m_size - m_hitSize)/2;

	if(m_pointType == POINT_LEFTTOP)		// 左上原点の場合
	{
		self[0].x = m_pos.x + m_hitOffset.x + temp.x;				self[0].y = m_pos.y + m_hitOffset.y + temp.y;
		self[1].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = m_pos.y + m_hitOffset.y + temp.y;
		self[2].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		self[3].x = m_pos.x + m_hitOffset.x + temp.x;				self[3].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
	}
	else if(m_pointType == POINT_CENTER)	// 中心原点の場合
	{
		self[0].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[1].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[2].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		self[3].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
	}

	// 頂点座標
	m_hitBox[0].vtx = D3DXVECTOR3(self[0].x, self[0].y, 0);
	m_hitBox[1].vtx = D3DXVECTOR3(self[1].x, self[1].y, 0);
	m_hitBox[2].vtx = D3DXVECTOR3(self[3].x, self[3].y, 0);
	m_hitBox[3].vtx = D3DXVECTOR3(self[2].x, self[2].y, 0);

	// テクスチャ座標
	m_hitBox[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_hitBox[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_hitBox[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_hitBox[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 色情報
	for(int cnt = 0; cnt < 4; cnt++)
	{
		m_hitBox[cnt].diffuse	= D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f);
		m_hitBox[cnt].rhw		= 1.0f;
	}

	//頂点フォーマットの設定
	m_device->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	m_device->SetTexture(0, NULL);

	//描画設定
	m_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
								2,
								m_hitBox,
								sizeof(VERTEX_2D));
}