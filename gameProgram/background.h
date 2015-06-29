//*****************************************************************************
//
// CBackgroundクラス [background.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_BACKGROUND_H
#define _MY_BACKGROUND_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義構造体
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 画像データ識別
enum BG_TYPE
{
	TYPE_FOREST_01 = 0,
	TYPE_TWON_01
};

// 背景情報
struct BG_DATA
{
	BG_TYPE type;
	int index;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBackground : CScene2D
{
public:
	CBackground(int priority = 1, OBJTYPE objType = OBJTYPE_2D);
	~CBackground(){};

	static CBackground* Create(LPDIRECT3DDEVICE9 device, BG_DATA data);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void Scroll(float scroll){SetPosX(m_pos.x - scroll);}

	void		 SetBgNext(CBackground* next){m_next = next;}
	CBackground* GetBgNext(void){return m_next;}
	void		 SetBgPrev(CBackground* prev){m_prev = prev;}
	CBackground* GetBgPrev(void){return m_prev;}

private:
	CBackground* m_next;	// 次へのポインタ
	CBackground* m_prev;	// 前へのポインタ
};

//=============================================================================
#endif
