
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
		SKY_BG,
		SKY1,
		SKY2,
		SKY3,
		SKY4,
		SKY5,

		// 森
		FOREST_01,

		// 町
		TOWN_01,

		// 道
		DIRT,
		ASPHALT,

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
		ASSY_TRAM,
		ASSY_LOG,
		ASSY_BATHTUB,
		ASSY_DOLLY,
		ASSY_SLEIGH,
		ASSY_TRUCK,

		//キャラメイク画面UI
		MAKE_UI_ASSY_OPTION,
		MAKE_UI_COS_OPTION,
		MAKE_UI_COS_DETAIL,
		MAKE_UI_SELECT_CUR,
		MAKE_UI_SELECT_FRAME,
		MAKE_UI_SELECT_BACK,

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