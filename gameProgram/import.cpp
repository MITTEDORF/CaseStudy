//*****************************************************************************
//
// CImportクラス [import.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// テクスチャ
const char* TEX_PATH[] =
{
	NULL,

	// システム
	"./data/TEXTURE/fade.jpg",
	"./data/TEXTURE/version/beta.png",

	// タイトル
	"./data/TEXTURE/title/titleLogo.png",
	"./data/TEXTURE/title/title_bg.png",

	// 空
	"./data/TEXTURE/sky/sky_back.png",
	"./data/TEXTURE/sky/sky_01.png",
	"./data/TEXTURE/sky/sky_02.png",
	"./data/TEXTURE/sky/sky_03.png",
	"./data/TEXTURE/sky/sky_04.png",
	"./data/TEXTURE/sky/sky_05.png",

	// 森
	"./data/TEXTURE/forest/forest_01.png",

	// 町
	"./data/TEXTURE/town/town_01.png",

	// 道
	"./data/TEXTURE/forest/dirt.png",
	"./data/TEXTURE/town/asphalt.png",

	// 障害物
	"./data/TEXTURE/stumbler/signboard.png",
	"./data/TEXTURE/stumbler/lion.png",
	"./data/TEXTURE/stumbler/rock.png",
	"./data/TEXTURE/stumbler/log_left.png",
	"./data/TEXTURE/stumbler/log_center.png",
	"./data/TEXTURE/stumbler/log_right.png",
	"./data/TEXTURE/stumbler/bird.png",
	"./data/TEXTURE/stumbler/dustbox.png",
	"./data/TEXTURE/stumbler/barricade.png",

	// ターゲット
	"./data/TEXTURE/goal/tv_on.png",
	"./data/TEXTURE/goal/tv_on.png",
	"./data/TEXTURE/goal/tv_off.png",
	"./data/TEXTURE/goal/tv_clear.png",

	// プレイヤー
	"./data/TEXTURE/player/default/player_wait.png",
	"./data/TEXTURE/player/default/player_attack.png",
	"./data/TEXTURE/player/default/player_light.png",

	"./data/TEXTURE/player/knight/player_wait.png",
	"./data/TEXTURE/player/knight/player_attack.png",
	"./data/TEXTURE/player/knight/player_light.png",

	"./data/TEXTURE/player/santa/player_wait.png",
	"./data/TEXTURE/player/santa/player_attack.png",
	"./data/TEXTURE/player/santa/player_light.png",

	"./data/TEXTURE/player/swimwear/player_wait.png",
	"./data/TEXTURE/player/swimwear/player_attack.png",
	"./data/TEXTURE/player/swimwear/player_light.png",
	
	"./data/TEXTURE/player/ninja/player_wait.png",
	"./data/TEXTURE/player/ninja/player_attack.png",
	"./data/TEXTURE/player/ninja/player_light.png",

	"./data/TEXTURE/player/faiter/player_wait.png",
	"./data/TEXTURE/player/faiter/player_attack.png",
	"./data/TEXTURE/player/faiter/player_light.png",


	"./data/TEXTURE/player/player_goodmood.png",
	"./data/TEXTURE/player/player_badmood.png",

	//パーティクル
	"./data/TEXTURE/particle/particle_yellow_small.png",
	"./data/TEXTURE/particle/particle_daidai_small.png",
	"./data/TEXTURE/particle/particle_white_small.png",

	// 乗り物
	"./data/TEXTURE/assy/tram.png",
	"./data/TEXTURE/assy/log.png",
	"./data/TEXTURE/assy/bathtub.png",
	"./data/TEXTURE/assy/dolly.png",
	"./data/TEXTURE/assy/sleigh.png",
	"./data/TEXTURE/assy/truck.png",

	//キャラメイク画面UI
	"./data/TEXTURE/select/assy_option.png",
	"./data/TEXTURE/select/costume_option.png",
	"./data/TEXTURE/select/option_details.png",
	"./data/TEXTURE/select/select_cursor.png",
	"./data/TEXTURE/select/select_frame.png"


};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9	CImport::m_tex[TEX_MAX];

//=============================================================================
// コンストラクタ
//=============================================================================
CImport::CImport(void)
{
	// テクスチャ
	for(int cnt = 0; cnt < TEX_MAX; ++cnt)
	{
		m_tex[cnt] = nullptr;
	}
}

//=============================================================================
// 生成
//=============================================================================
CImport* CImport::Create(LPDIRECT3DDEVICE9 device)
{
	CImport* pointer = new CImport;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CImport::Init(LPDIRECT3DDEVICE9 device)
{
	HRESULT hr;

	//----------------------------
	// テクスチャ
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; ++cnt)
	{
		hr = D3DXCreateTextureFromFile(device, TEX_PATH[cnt], &m_tex[cnt]);
		if(FAILED(hr))
		{
			MessageBox(NULL, "テクスチャ無し", "D3DXCreateTextureFromFile", MB_OK);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CImport::Uninit(void)
{
	//----------------------------
	// テクスチャ
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; cnt++)
	{
		// テクスチャの開放
		SAFE_RELEASE(m_tex[cnt]);
	}
}
