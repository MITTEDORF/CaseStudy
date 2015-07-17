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

#include "mapData.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// テクスチャ
const char* TEX_PATH[] =
{
	NULL,

	// システム
	"./habahiro_data/TEXTURE/fade.jpg",

	// タイトル
	"./habahiro_data/TEXTURE/title/titleLogo.png",
	"./habahiro_data/TEXTURE/title/title_bg.png",
	"./habahiro_data/TEXTURE/title/enter.png",
	"./habahiro_data/TEXTURE/title/close.png",
	"./habahiro_data/TEXTURE/title/close_large.png",

	// 空
	"./habahiro_data/TEXTURE/sky/sky_01.png",
	"./habahiro_data/TEXTURE/sky/sky_02.png",
	"./habahiro_data/TEXTURE/sky/sky_03.png",
	"./habahiro_data/TEXTURE/sky/sky_04.png",
	"./habahiro_data/TEXTURE/sky/sky_05.png",

	// 森
	"./habahiro_data/TEXTURE/forest/forest_01.png",

	// 水辺
	"./habahiro_data/TEXTURE/waterside/waterside_01.png",

	// 砂漠
	"./habahiro_data/TEXTURE/desert/desert_01.png",
	"./habahiro_data/TEXTURE/desert/desert_02.png",
	"./habahiro_data/TEXTURE/desert/desert_03.png",

	// 氷河
	"./habahiro_data/TEXTURE/glacier/glacier_01.png",
	"./habahiro_data/TEXTURE/glacier/glacier_02.png",
	"./habahiro_data/TEXTURE/glacier/glacier_03.png",
	"./habahiro_data/TEXTURE/glacier/glacier_04.png",
	"./habahiro_data/TEXTURE/glacier/glacier_05.png",

	// サバンナ
	"./habahiro_data/TEXTURE/savannah/savannah_01.png",
	"./habahiro_data/TEXTURE/savannah/savannah_02.png",
	"./habahiro_data/TEXTURE/savannah/savannah_03.png",
	"./habahiro_data/TEXTURE/savannah/savannah_04.png",
	"./habahiro_data/TEXTURE/savannah/savannah_05.png",

	// 道
	"./habahiro_data/TEXTURE/forest/dirt.png",
	"./habahiro_data/TEXTURE/desert/sand.png",
	"./habahiro_data/TEXTURE/glacier/ice.png",
	"./habahiro_data/TEXTURE/savannah/grassfield.png",
	"./habahiro_data/TEXTURE/waterside/water.png",

	// 障害物
	"./habahiro_data/TEXTURE/stumbler/signboard.png",
	"./habahiro_data/TEXTURE/stumbler/lion.png",
	"./habahiro_data/TEXTURE/stumbler/rock.png",
	"./habahiro_data/TEXTURE/stumbler/log_left.png",
	"./habahiro_data/TEXTURE/stumbler/log_center.png",
	"./habahiro_data/TEXTURE/stumbler/log_right.png",
	"./habahiro_data/TEXTURE/stumbler/bird.png",
	"./habahiro_data/TEXTURE/stumbler/dustbox.png",
	"./habahiro_data/TEXTURE/stumbler/barricade.png",
	"./habahiro_data/TEXTURE/stumbler/cuctus.png",
	"./habahiro_data/TEXTURE/stumbler/iceberg.png",
	"./habahiro_data/TEXTURE/stumbler/icicle.png",
	"./habahiro_data/TEXTURE/stumbler/nuts.png",
	"./habahiro_data/TEXTURE/stumbler/nuts_reverse.png",
	"./habahiro_data/TEXTURE/stumbler/sandstone.png",
	"./habahiro_data/TEXTURE/stumbler/bee.png",
	"./habahiro_data/TEXTURE/stumbler/huneycomb.png",
	"./habahiro_data/TEXTURE/stumbler/stump.png",

	// ターゲット
	"./habahiro_data/TEXTURE/goal/tv_off.png",
	"./habahiro_data/TEXTURE/goal/tv_on.png",
	"./habahiro_data/TEXTURE/goal/tv_off.png",
	"./habahiro_data/TEXTURE/goal/tv_on.png",
	"./habahiro_data/TEXTURE/goal/tv_clear.png",

	// プレイヤー
	"./habahiro_data/TEXTURE/player/default/player_wait.png",
	"./habahiro_data/TEXTURE/player/default/player_attack.png",
	"./habahiro_data/TEXTURE/player/default/player_light.png",

	"./habahiro_data/TEXTURE/player/knight/player_wait.png",
	"./habahiro_data/TEXTURE/player/knight/player_attack.png",
	"./habahiro_data/TEXTURE/player/knight/player_light.png",

	"./habahiro_data/TEXTURE/player/santa/player_wait.png",
	"./habahiro_data/TEXTURE/player/santa/player_attack.png",
	"./habahiro_data/TEXTURE/player/santa/player_light.png",

	"./habahiro_data/TEXTURE/player/swimwear/player_wait.png",
	"./habahiro_data/TEXTURE/player/swimwear/player_attack.png",
	"./habahiro_data/TEXTURE/player/swimwear/player_light.png",
	
	"./habahiro_data/TEXTURE/player/ninja/player_wait.png",
	"./habahiro_data/TEXTURE/player/ninja/player_attack.png",
	"./habahiro_data/TEXTURE/player/ninja/player_light.png",

	"./habahiro_data/TEXTURE/player/faiter/player_wait.png",
	"./habahiro_data/TEXTURE/player/faiter/player_attack.png",
	"./habahiro_data/TEXTURE/player/faiter/player_light.png",


	"./habahiro_data/TEXTURE/player/player_goodmood.png",
	"./habahiro_data/TEXTURE/player/player_badmood.png",

	//パーティクル
	"./habahiro_data/TEXTURE/particle/particle_yellow_small.png",
	"./habahiro_data/TEXTURE/particle/particle_daidai_small.png",
	"./habahiro_data/TEXTURE/particle/particle_white_small.png",

	// 乗り物
	"./habahiro_data/TEXTURE/assy/truck.png",
	"./habahiro_data/TEXTURE/assy/dolly.png",
	"./habahiro_data/TEXTURE/assy/tram.png",
	"./habahiro_data/TEXTURE/assy/log.png",
	"./habahiro_data/TEXTURE/assy/bathtub.png",
	"./habahiro_data/TEXTURE/assy/sleigh.png",

	//キャラメイク画面UI
	"./habahiro_data/TEXTURE/select/assy_option.png",
	"./habahiro_data/TEXTURE/select/costume_option.png",
	"./habahiro_data/TEXTURE/select/option_details.png",
	"./habahiro_data/TEXTURE/select/select_cursor.png",
	"./habahiro_data/TEXTURE/select/select_frame.png",
	"./habahiro_data/TEXTURE/select/select_bg.png",
	"./habahiro_data/TEXTURE/select/costume/cos_none.png",
	"./habahiro_data/TEXTURE/select/costume/cos_knight.png",
	"./habahiro_data/TEXTURE/select/costume/cos_santa.png",
	"./habahiro_data/TEXTURE/select/costume/cos_swimwear.png",
	"./habahiro_data/TEXTURE/select/costume/cos_ninja.png",
	"./habahiro_data/TEXTURE/select/costume/cos_fighter.png",
	"./habahiro_data/TEXTURE/select/message/costume/cos_mes_knight.png",
	"./habahiro_data/TEXTURE/select/message/costume/cos_mes_santa.png",
	"./habahiro_data/TEXTURE/select/message/costume/cos_mes_swim.png",
	"./habahiro_data/TEXTURE/select/message/costume/cos_mes_ninja.png",
	"./habahiro_data/TEXTURE/select/message/costume/cos_mes_fighter.png",
	"./habahiro_data/TEXTURE/select/vehicle/veh_trum.png",
	"./habahiro_data/TEXTURE/select/vehicle/veh_dolly.png",
	"./habahiro_data/TEXTURE/select/vehicle/veh_log.png",
	"./habahiro_data/TEXTURE/select/vehicle/veh_bathtub.png",
	"./habahiro_data/TEXTURE/select/vehicle/veh_sleigh.png",
	"./habahiro_data/TEXTURE/select/vehicle/veh_truck.png",
	"./habahiro_data/TEXTURE/select/message/vehicle/veh_mes_trum.png",
	"./habahiro_data/TEXTURE/select/message/vehicle/veh_mes_dolly.png",
	"./habahiro_data/TEXTURE/select/message/vehicle/veh_mes_log.png",
	"./habahiro_data/TEXTURE/select/message/vehicle/veh_mes_bathtub.png",
	"./habahiro_data/TEXTURE/select/message/vehicle/veh_mes_sleigh.png",
	"./habahiro_data/TEXTURE/select/hyphen_3.png",
	"./habahiro_data/TEXTURE/select/hyphen_4.png",
	"./habahiro_data/TEXTURE/select/hyphen_5.png",
	"./habahiro_data/TEXTURE/select/hyphen_long.png",
	"./habahiro_data/TEXTURE/select/char_sel_back_01.png",
	"./habahiro_data/TEXTURE/select/char_sel_chip_01.png",
	"./habahiro_data/TEXTURE/select/char_sel_back_02.png",
	"./habahiro_data/TEXTURE/select/char_sel_chip_02.png",
	"./habahiro_data/TEXTURE/select/char_sel_back_03.png",
	"./habahiro_data/TEXTURE/select/char_sel_chip_03.png",

	// 文字素材
	"./habahiro_data/TEXTURE/number/coron.png",
	"./habahiro_data/TEXTURE/number/coron_half.png",
	"./habahiro_data/TEXTURE/number/number.png",
	"./habahiro_data/TEXTURE/countdown/countdown_num.png",
	"./habahiro_data/TEXTURE/countdown/start.png",
	"./habahiro_data/TEXTURE/select/message.png",

	//ステージセレクト用
	"./habahiro_data/TEXTURE/stageselect/map.png",
	"./habahiro_data/TEXTURE/stageselect/icon_desert.png",
	"./habahiro_data/TEXTURE/stageselect/icon_forest.png",
	"./habahiro_data/TEXTURE/stageselect/icon_glacier.png",
	"./habahiro_data/TEXTURE/stageselect/icon_savannah.png",
	"./habahiro_data/TEXTURE/stageselect/icon_waterside.png",
	"./habahiro_data/TEXTURE/stageselect/selectstage.png",

	// リザルト
	"./habahiro_data/TEXTURE/result/clock.png",
	"./habahiro_data/TEXTURE/result/score.png",
	"./habahiro_data/TEXTURE/result/result_bg.png",

	//ゴールの時に駆け寄ってくる存在
	"./habahiro_data/TEXTURE/goal/goalchar_right.png",
	"./habahiro_data/TEXTURE/goal/goalchar_left.png"
};

// マップ
const char* MAP_PATH[] =
{
	"./habahiro_data/MAP/stage_desert.txt",
	"./habahiro_data/MAP/stage_waterside.txt",
	"./habahiro_data/MAP/stage_glacier.txt",
	"./habahiro_data/MAP/stage_savannah.txt",
	"./habahiro_data/MAP/stage_forest.txt"

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9	CImport::m_tex[TEX_MAX];
CMapData*			CImport::m_map[STAGE_MAX];

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

	//----------------------------
	// マップ
	//----------------------------
	for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	{
		m_map[cnt] = CMapData::Create(MAP_PATH[cnt]);
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

	//----------------------------
	// マップ
	//----------------------------
	for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	{
		// テクスチャの開放
		SAFE_END(m_map[cnt]);
	}
}
