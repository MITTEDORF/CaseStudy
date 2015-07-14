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
	m_next = NULL;
	m_prev = NULL;
	m_move = D3DXVECTOR2(-1.0f, -1.0f);
	m_defpos = D3DXVECTOR2(0.0f, 0.0f);
	m_texAnim = 0;
	m_fallFrag = false;
	m_stumDelete = false;
}

//=============================================================================
// 生成
//=============================================================================
CStumbler* CStumbler::Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType)
{
	// 当たり判定大きさリスト
	D3DXVECTOR2 Size_List[] =
	{
		D3DXVECTOR2(112, 128),		// TYPE_SIGNBOARD
		D3DXVECTOR2(112, 112),		// TYPE_LION
		D3DXVECTOR2(128, 96),		// TYPE_ROCK
		D3DXVECTOR2(128, 128),		// TYPE_LOG_LEFT
		D3DXVECTOR2(128, 128),		// TYPE_LOG_CENTER
		D3DXVECTOR2(128, 128),		// TYPE_LOG_RIGHT
		D3DXVECTOR2(96, 96),		// TYPE_BIRD
		D3DXVECTOR2(80, 96),		// TYPE_DUSTBOX
		D3DXVECTOR2(198, 112),		// TYPE_BARRICADE
		D3DXVECTOR2(128, 128),		// TYPE_CUCTUS
		D3DXVECTOR2(128, 128),		// TYPE_ICEBERG
		D3DXVECTOR2(128, 128),		// TYPE_ICICLE
		D3DXVECTOR2(128, 128),		// TYPE_NUTS
		D3DXVECTOR2(128, 128),		// TYPE_NUTS_REVERSE
		D3DXVECTOR2(128, 128),		// TYPE_SANDSTONE
		D3DXVECTOR2(128, 128),		// TYPE_BEE
		D3DXVECTOR2(128, 128),		// TYPE_HUNEYCOMB
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
		D3DXVECTOR2(0, 8),			// TYPE_BARRICADE
		D3DXVECTOR2(0, 0),			// TYPE_CUCTUS
		D3DXVECTOR2(0, 0),			// TYPE_ICEBERG
		D3DXVECTOR2(0, 0),			// TYPE_ICICLE
		D3DXVECTOR2(0, 0),			// TYPE_NUTS
		D3DXVECTOR2(0, 0),			// TYPE_NUTS_REVERSE
		D3DXVECTOR2(0, 0),			// TYPE_SANDSTONE
		D3DXVECTOR2(0, 0),			// TYPE_BEE
		D3DXVECTOR2(0, 0),			// TYPE_HUNEYCOMB
	};

	CStumbler* pointer = new CStumbler;
	pointer->Init(device, (CImport::TEXTURES)(CImport::SIGNBOARD + data.type), pointType);

	// データを元に座標の変更
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));

	// デフォルト位置セット処理
	pointer->SetDefPos(pointer->GetPos());

	// 障害物タイプによる当たり判定の変更
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);

	// 障害物タイプの保存
	pointer->SetStumType(data.type);

	// 障害物タイプによってはデータの変更
	switch(data.type)
	{
	case TYPE_BIRD:
		pointer->SetCord(0, D3DXVECTOR2(0, 0));
		pointer->SetCord(1, D3DXVECTOR2(0.5, 0));
		pointer->SetCord(2, D3DXVECTOR2(0, 1));
		pointer->SetCord(3, D3DXVECTOR2(0.5, 1));
		break;

	case TYPE_BARRICADE:
		pointer->SetSize(256.0f, 128.0f);
		break;

	case TYPE_BEE:
		pointer->SetCord(0, D3DXVECTOR2(0, 0));
		pointer->SetCord(1, D3DXVECTOR2(0.25, 0));
		pointer->SetCord(2, D3DXVECTOR2(0, 1));
		pointer->SetCord(3, D3DXVECTOR2(0.25, 1));
		pointer->SetStumMove(D3DXVECTOR2(-4.0f, -4.0f));
		break;

	default:
		break;
	}

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
	// HPが0以下なら削除フラグ立てる
	if(m_life <= 0)
	{
		// 削除フラグ立てる
		SetStumDelete();
	}
	else
	{
		// タイプによって色々処理
		switch(m_type)
		{
		case TYPE_BIRD:			// カラスの時
			// 上下移動
			CScene2D::SetPosY(m_pos.y + m_move.y);
			// デフォルト位置との開きが規定値を超えたら反転
			if(abs(m_defpos.y - m_pos.y) > 45.0f)
				m_move.y *= -1;
			// 12fごとにテクスチャアニメーション
			m_texAnim++;
			if(m_texAnim % 12 == 0)
			{
				if(m_coord[0].x != 0.5f)
				{
					CScene2D::SetCord(0, D3DXVECTOR2(0.5, 0));
					CScene2D::SetCord(1, D3DXVECTOR2(1, 0));
					CScene2D::SetCord(2, D3DXVECTOR2(0.5, 1));
					CScene2D::SetCord(3, D3DXVECTOR2(1, 1));
				}
				else
				{
					CScene2D::SetCord(0, D3DXVECTOR2(0, 0));
					CScene2D::SetCord(1, D3DXVECTOR2(0.5, 0));
					CScene2D::SetCord(2, D3DXVECTOR2(0, 1));
					CScene2D::SetCord(3, D3DXVECTOR2(0.5, 1));
				}
			}
			break;

		case TYPE_BEE:		// 蜂の時
			// 左右移動
			CScene2D::SetPosX(m_pos.x + m_move.x);
			// デフォルト位置との開きが規定値を超えたら反転
			if(abs(m_defpos.x - m_pos.x) > 96.0f)
			{
				m_move.x *= -1;
			}

			// 上下移動
			CScene2D::SetPosY(m_pos.y + m_move.y);
			// デフォルト位置との開きが規定値を超えたら反転
			if(abs(m_defpos.y - m_pos.y) > 48.0f)
			{
				m_move.y *= -1;
			}

			// 8fごとにテクスチャアニメーション
			m_texAnim++;
			if(m_texAnim % 8 == 0)
			{
				if(m_coord[0].x != 0.75f)
				{
					D3DXVECTOR2 tmp;
					for(int i = 0; i < 4;  i++)
					{
						tmp = CScene2D::GetCord(i);
						tmp.x += 0.25;
						CScene2D::SetCord(i, tmp);
					}
				}
				else
				{
					CScene2D::SetCord(0, D3DXVECTOR2(0, 0));
					CScene2D::SetCord(1, D3DXVECTOR2(0.25, 0));
					CScene2D::SetCord(2, D3DXVECTOR2(0, 1));
					CScene2D::SetCord(3, D3DXVECTOR2(0.25, 1));
				}
			}
			break;

		case TYPE_NUTS:
		case TYPE_NUTS_REVERSE:
		case TYPE_ICICLE:			// 落ち物トラップ類
			if(m_fallFrag)
			{
				m_texAnim++;
				// 30f横揺れする
				if(m_texAnim < 30)
					if(m_texAnim % 4 == 0 || m_texAnim % 4 == 1)
					{
						CScene2D::SetPosX(m_pos.x += 16.0f);
					}
					else
					{
						CScene2D::SetPosX(m_pos.x -= 16.0f);
					}
				// 待機フレーム経過後落下
				else
					CScene2D::SetPosY(m_pos.y += 16.0f);
				// 画面下に出たら死ね
				if(m_pos.y >= 760.0f)
				{
					SetStumDelete();
				}
			}
			break;

		default:
			break;
		}
		// 継承元の更新処理呼び出し
		CScene2D::Update();
	}
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
// 落ち物が落ちるかどうかの判定
//=============================================================================
void CStumbler::CheckFall(D3DXVECTOR2 pos)
{
	if(pos.x >= m_pos.x - (SCREEN_HEIGHT - m_pos.y)/2)
	{
		SetFall();
	}
}