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

// 当たり判定大きさリスト
D3DXVECTOR2 Size_List[] =
{
	D3DXVECTOR2(112, 128),		// TYPE_SIGNBOARD
	D3DXVECTOR2(112, 112),		// TYPE_LION
	D3DXVECTOR2(128, 96),		// TYPE_ROCK
	D3DXVECTOR2(128, 128),		// TYPE_LOG_LEFT
	D3DXVECTOR2(128, 128),		// TYPE_LOG_CENTER
	D3DXVECTOR2(128, 128),		// TYPE_LOG_RIGHT
	D3DXVECTOR2(128, 128),		// TYPE_BIRD
	D3DXVECTOR2(80, 96),		// TYPE_DUSTBOX
	D3DXVECTOR2(128, 128),		// TYPE_BARRICADE
	D3DXVECTOR2(128, 128)		// TYPE_MAX
};

// 当たり判定座標オフセット値リスト
D3DXVECTOR2 Offset_List[] =
{
	D3DXVECTOR2(0, 0),			// TYPE_SIGNBOARD
	D3DXVECTOR2(0, 8),			// TYPE_LION
	D3DXVECTOR2(0, 16),			// TYPE_ROCK
	D3DXVECTOR2(0, 0),			// TYPE_LOG_LEFT
	D3DXVECTOR2(0, 0),			// TYPE_LOG_CENTER
	D3DXVECTOR2(0, 0),			// TYPE_LOG_RIGHT
	D3DXVECTOR2(0, 0),			// TYPE_BIRD
	D3DXVECTOR2(0, 16),			// TYPE_DUSTBOX
	D3DXVECTOR2(0, 0),			// TYPE_BARRICADE
	D3DXVECTOR2(0, 0)			// TYPE_MAX
};

//=============================================================================
// コンストラクタ
//=============================================================================
CStumbler::CStumbler(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_life = 1;
	m_next = NULL;
	m_prev = NULL;
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
	// 障害物タイプによる当たり判定の変更
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);
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

	// 当たり判定ボックスの描画
	DrawHitBox();
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