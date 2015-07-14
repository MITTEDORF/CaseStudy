//*****************************************************************************
//
// loading_iconクラス [loading_icon.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "loading_icon.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const float CLIcon::POLYGON_SIZE = 256.0f;
//=============================================================================
// コンストラクタ
//=============================================================================
CLIcon::CLIcon()
{
	m_texture	= NULL;
	m_localTex	= false;

	m_rot	= 0.0f;
	m_pos	= D3DXVECTOR2(0.0f, 0.0f);
	m_size	= D3DXVECTOR2(POLYGON_SIZE, POLYGON_SIZE);
	m_color	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR2 half = D3DXVECTOR2(m_size.x / 2.0f, m_size.y / 2.0f);
	m_length = DISTANCE_2D(half.x, half.y);
	m_angle	 = atan2f(half.x, half.y);
	m_anim_now = 0;
	m_anim_period = 0;
	m_coord[0] = D3DXVECTOR2(0.0f*0.25f, 0.0f);
	m_coord[1] = D3DXVECTOR2(1.0f*0.25f, 0.0f);
	m_coord[2] = D3DXVECTOR2(0.0f*0.25f, 1.0f);
	m_coord[3] = D3DXVECTOR2(1.0f*0.25f, 1.0f);

}
CLIcon* CLIcon::Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , D3DXVECTOR2 pos )
{
	CLIcon* pointer = new CLIcon();
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	return pointer;

}
CLIcon* CLIcon::Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType , D3DXVECTOR2 pos )
{
	CLIcon* pointer = new CLIcon();
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	return pointer;

}
HRESULT CLIcon::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
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

	// 頂点情報設定
	SetVertexPolygon();

	// テクスチャ取得
	m_file_path = (const char*)texture;
	m_texture = CImport::GetTexture(texture);
	m_localTex	= false;

	return S_OK;

}
HRESULT CLIcon::Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
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

	// 頂点情報設定
	SetVertexPolygon();
	m_file_path = texture;
	// テクスチャ取得
	D3DXCreateTextureFromFile(device, texture, &m_texture);
	m_localTex = true;
	
	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}
void CLIcon::Uninit(void)
{
	if(m_localTex)
	{
		SAFE_RELEASE(m_texture);
	}

	delete this;
}
void CLIcon::Update(void)
{
	if( m_anim_now < ANIMATION_MAX )
	{
		m_anim_period++;
		if( m_anim_period >= ANIMATION_PERIOD )
		{
			m_anim_now+=1;
			m_anim_period = 0;
		}
	}
	else
	{
		m_anim_now = 0;
	}

}
void CLIcon::Draw(void)
{
	SetVertexPolygon();
	//頂点フォーマットの設定
	m_device->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	m_device->SetTexture(0, m_texture);
	m_device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_vtx[0] , sizeof(VERTEX_2D) );

}
void CLIcon::SetVertexPolygon( void )
{
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

	// 座標
	m_vtx[0].vtx = D3DXVECTOR3(work[0].x, work[0].y, 0.0f);
	m_vtx[1].vtx = D3DXVECTOR3(work[1].x, work[1].y, 0.0f);
	m_vtx[2].vtx = D3DXVECTOR3(work[2].x, work[2].y, 0.0f);
	m_vtx[3].vtx = D3DXVECTOR3(work[3].x, work[3].y, 0.0f);

	// 1.0f固定
	m_vtx[0].rhw = 1.0f;
	m_vtx[1].rhw = 1.0f;
	m_vtx[2].rhw = 1.0f;
	m_vtx[3].rhw = 1.0f;

	// 反射光
	m_vtx[0].diffuse = m_color;
	m_vtx[1].diffuse = m_color;
	m_vtx[2].diffuse = m_color;
	m_vtx[3].diffuse = m_color;

	// テクスチャ座標
	m_vtx[0].tex = D3DXVECTOR2(m_coord[0].x+((m_anim_now+1)*0.25f), m_coord[0].y);
	m_vtx[1].tex = D3DXVECTOR2(m_coord[1].x+((m_anim_now+1)*0.25f), m_coord[1].y);
	m_vtx[2].tex = D3DXVECTOR2(m_coord[2].x+((m_anim_now+1)*0.25f), m_coord[2].y);
	m_vtx[3].tex = D3DXVECTOR2(m_coord[3].x+((m_anim_now+1)*0.25f), m_coord[3].y);
}