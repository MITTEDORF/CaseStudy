
//*****************************************************************************
//
// CImportクラス [import.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_IMPORT_H
#define _MY_IMPORT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CMapData;

class CImport
{
public:
	enum TEXTURES
	{
		// なし
		NONE = 0,

		// システム
		FADE,
		VERSION,

		// タイトル
		TITLELOGO,
		TITLEBG,

		// 空
		SKY1,
		SKY2,
		SKY3,
		SKY4,
		SKY5,

		// 森
		FOREST_01,

		// 水辺
		WATERSIDE_01,

		// 砂漠
		DESERT_01,
		DESERT_02,
		DESERT_03,

		// 氷河
		GLACIER_01,
		GLACIER_02,
		GLACIER_03,
		GLACIER_04,
		GLACIER_05,

		// サバンナ
		SAVANNAH_01,
		SAVANNAH_02,
		SAVANNAH_03,
		SAVANNAH_04,
		SAVANNAH_05,

		// 道
		DIRT,
		SAND,
		ICE,
		GRASSFIELD,
		WATER,

		// 障害物
		SIGNBOARD,
		LION,
		ROCK,
		LOG_LEFT,
		LOG_CENTER,
		LOG_RIGHT,
		BIRD,
		DUSTBOX,
		BARRICADE,
		CUCTUS,
		ICEBERG,
		ICICLE,
		NUTS,
		NUTS_REVERSE,
		SANDSTONE,
		BEE,
		HUNEYCOMB,

		// ターゲット
		TARGET_OFF,
		TARGET_ON,
		GOAL_OFF,
		GOAL_ON,
		GOAL_CLEAR,

		// プレイヤー
		PLAYER_DEFAULT_WAIT,
		PLAYER_DEFAULT_ATTACK,
		PLAYER_DEFAULT_LIGHT,
		
		PLAYER_KNIGHT_WAIT,
		PLAYER_KNIGHT_ATTACK,
		PLAYER_KNIGHT_LIGHT,

		PLAYER_SANTA_WAIT,
		PLAYER_SANTA_ATTACK,
		PLAYER_SANTA_LIGHT,

		PLAYER_SWIMWEAR_WAIT,
		PLAYER_SWIMWEAR_ATTACK,
		PLAYER_SWIMWEAR_LIGHT,

		PLAYER_NINJA_WAIT,
		PLAYER_NINJA_ATTACK,
		PLAYER_NINJA_LIGHT,

		PLAYER_FAITER_WAIT,
		PLAYER_FAITER_ATTACK,
		PLAYER_FAITER_LIGHT,

		PLAYER_GOODMOOD,
		PLAYER_BADMOOD,

		//パーティクル
		PARTICLE_YELLOW_SMALL,
		PARTICLE_DAIDAI_SMALL,
		PARTICLE_WHITE_SMALL,

		// 乗り物
		ASSY_TRUCK,
		ASSY_DOLLY,
		ASSY_TRAM,
		ASSY_LOG,
		ASSY_BATHTUB,
		ASSY_SLEIGH,

		//キャラメイク画面UI
		MAKE_UI_ASSY_OPTION,
		MAKE_UI_COS_OPTION,
		MAKE_UI_COS_DETAIL,
		MAKE_UI_SELECT_CUR,
		MAKE_UI_SELECT_FRAME,
		MAKE_UI_SELECT_BACK,
		MAKE_UI_COS_NONE,
		MAKE_UI_COS_KNIGHT,
		MAKE_UI_COS_SANTA,
		MAKE_UI_COS_SWIM,
		MAKE_UI_COS_NINJA,
		MAKE_UI_COS_FIGHTER,
		MAKE_UI_COS_MES_KNIGHT,
		MAKE_UI_COS_MES_SANTA,
		MAKE_UI_COS_MES_SWIM,
		MAKE_UI_COS_MES_NINJA,
		MAKE_UI_COS_MES_FIGHTER,
		MAKE_UI_VEH_TRUM,
		MAKE_UI_VEH_DOLLY,
		MAKE_UI_VEH_LOG,
		MAKE_UI_VEH_BATHTUB,
		MAKE_UI_VEH_SLEIGH,
		MAKE_UI_VEH_TRUCK,
		MAKE_UI_VEH_MES_TRUM,
		MAKE_UI_VEH_MES_DOLLY,
		MAKE_UI_VEH_MES_LOG,
		MAKE_UI_VEH_MES_BATHTUB,
		MAKE_UI_VEH_MES_SLEIGH,
		MAKE_UI_HYPHEN_3,
		MAKE_UI_HYPHEN_4,
		MAKE_UI_HYPHEN_5,
		MAKE_UI_HYPHEN_LONG,
		MAKE_UI_CHAR_SEL_BACK_01,
		MAKE_UI_CHAR_SEL_CHIP_01,

		// 文字素材
		COLON,
		COLON_HALF,
		NUMBER,

		//ステージセレクト用
		STAGE_SELECT_BG,
		STAGE_SELECT_DESERT,
		STAGE_SELECT_FOREST,
		STAGE_SELECT_GLACIER,
		STAGE_SELECT_SAVANNAH,
		STAGE_SELECT_WATERSIDE,


		TEX_MAX
	};

	enum MAPS
	{
		// 森（仮）
		STAGE_1_1 = 0,
		STAGE_MAX
	};

	CImport();
	~CImport(){};

	static	CImport* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);

	static LPDIRECT3DTEXTURE9	GetTexture(TEXTURES tex){return m_tex[tex];}
	static CMapData*			GetMap(MAPS map){return m_map[map];}

private:
	static LPDIRECT3DTEXTURE9	m_tex[TEX_MAX];
	static CMapData*			m_map[STAGE_MAX];
};

//=============================================================================
#endif