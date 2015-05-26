//*****************************************************************************
//
// CSkyクラス [sky.h]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "sky.h"

#include "scene2D.h"
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SKY_LEFT	(-SCREEN_WIDTH)
#define SKY_RIGHT	(SCREEN_WIDTH * (SKY_MAX - 2))

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// コンストラクタ
//=============================================================================
CSky::CSky(void)
{
}

//=============================================================================
// 生成
//=============================================================================
CSky* CSky::Create(LPDIRECT3DDEVICE9 device)
{
	CSky* pointer = new CSky;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSky::Init(LPDIRECT3DDEVICE9 device)
{
	for(int cnt = 0; cnt < SKY_MAX; ++cnt)
	{
		m_sky[cnt] = CScene2D::Create(device, (CImport::TEXTURES)(CImport::TEX_SKY1 + cnt), CScene2D::POINT_LEFTTOP);
		m_sky[cnt]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_sky[cnt]->SetPos(SCREEN_WIDTH * cnt, 0.0f);
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CSky::Uninit(void)
{
}

//=============================================================================
// スクロール
//=============================================================================
void CSky::Scroll(float scroll)
{
	for(int cnt = 0; cnt < SKY_MAX; ++cnt)
	{
		float skyScroll = m_sky[cnt]->GetPos().x - scroll;

		if(skyScroll <= SKY_LEFT)
		{
			skyScroll = SKY_RIGHT - scroll;
		}
		else if(skyScroll >= SKY_RIGHT)
		{
			skyScroll = SKY_LEFT;
		}

		m_sky[cnt]->SetPos(skyScroll, 0.0f);
	}
}
