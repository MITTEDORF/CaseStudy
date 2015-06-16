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
class CImport
{
public:
	typedef enum
	{
		NONE = 0,

		// システム
		FADE,
		VERSION,

		// ロゴ
		TITLELOGO,

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
		GOAL_OFF,
		GOAL_ON,
		GOAL_CLEAR,

		// プレイヤー
		PLAYER_WAIT,
		PLAYER_ATTACK,
		PLAYER_LIGHT,
		PLAYER_GOODMOOD,
		PLAYER_BADMOOD,

		//パーティクル
		PARTICLE_YELLOW_SMALL,
		PARTICLE_DAIDAI_SMALL,
		PARTICLE_WHITE_SMALL,

		// 乗り物
		ASSY_TRAM,

		TEX_MAX
	} TEXTURES;

	CImport();
	~CImport(){};

	static	CImport* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);

	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURES tex){return m_tex[tex];}

private:
	static LPDIRECT3DTEXTURE9 m_tex[TEX_MAX];;
};

//=============================================================================
#endif