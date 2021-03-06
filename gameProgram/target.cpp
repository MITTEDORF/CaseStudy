//*****************************************************************************
//
// targetクラス [target.cpp]
// Author : KEN MATSUURA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "target.h"

#include "listObject.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTarget::CTarget(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_next = NULL;
	m_prev = NULL;
	m_targetFlag = false;
	m_goalFlag = false;
}

//=============================================================================
// 生成
//=============================================================================
CTarget* CTarget::Create(LPDIRECT3DDEVICE9 device, TARGET_DATA data, POINT_TYPE pointType)
{
	// 当たり判定大きさリスト
	D3DXVECTOR2 Size_List[] =
	{
		D3DXVECTOR2(32, SCREEN_HEIGHT),		// GOAL_OFF
		D3DXVECTOR2(32, SCREEN_HEIGHT),		// GOAL_ON
		D3DXVECTOR2(32, SCREEN_HEIGHT)		// GOAL_CLEAR
	};

	// 当たり判定座標オフセット値リスト
	D3DXVECTOR2 Offset_List[] =
	{
		D3DXVECTOR2(0.0f, -232.0f),			// GOAL_OFF
		D3DXVECTOR2(0.0f, -232.0f),			// GOAL_ON
		D3DXVECTOR2(0.0f, -232.0f)			// GOAL_CLEAR
	};

	CTarget* pointer = new CTarget;
	pointer->Init(device, (CImport::TEXTURES)(CImport::TARGET_OFF + data.type), pointType);
	// データを元に座標の変更
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	// ターゲットタイプによる当たり判定の変更
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);
	// 光が収束するのかどうかのフラグ設定
	if(data.type == TYPE_TARGET_OFF)
	{
		pointer->SetTargetFrag(true);
		pointer->SetGoalFrag(false);
	}
	// ゴールするのかどうかのフラグ設定
	if(data.type == TYPE_GOAL_OFF || data.type == TYPE_GOAL_ON || data.type == TYPE_GOAL_CLEAR)
	{
		pointer->SetTargetFrag(false);
		pointer->SetGoalFrag(true);
	}
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTarget::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
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
void CTarget::Uninit(void)
{
	// 継承元の終了処理呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CTarget::Update(void)
{
	// 画面外カリング
	if(m_draw && (m_pos.x < -128 || m_pos.x > SCREEN_WIDTH))
	{
		CListObject::UnlinkDraw(this);
		m_draw = false;
	}
	else if(!m_draw)
	{
		CListObject::LinkDraw(this, GetPriority());
		m_draw = true;
	}

	// 継承元の更新処理呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画
//=============================================================================
void CTarget::Draw(void)
{
	// 継承元の描画処理呼び出し
	CScene2D::Draw();

	// 当たり判定ボックスの描画
	DrawHitBox();
}