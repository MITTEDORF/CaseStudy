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
		TEX_NONE = 0,

		// システム
		TEX_FADE,

		// ロゴ
		TEX_TITLELOGO,

		// 空
		TEX_SKY1,
		TEX_SKY2,
		TEX_SKY3,
		TEX_SKY4,
		TEX_SKY5,

		// 森
		TEX_DIRT,
		TEX_FOREST_01,

		// 町
		TEX_ASPHALT,
		TEX_TOWN_01,

		// プレイヤー
		TEX_PLAYER_WAIT,
		TEX_ASSY_TRAM,
		TEX_PLAY_ATTACK,

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