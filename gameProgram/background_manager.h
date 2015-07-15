//*****************************************************************************
//
// CBackgroundManagerクラス [background_manager.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_BACKGROUND_MANAGER_H
#define _MY_BACKGROUND_MANAGER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBackground;

class CBackgroundManager
{
public:
	CBackgroundManager();
	~CBackgroundManager(){};

	static	CBackgroundManager* Create(LPDIRECT3DDEVICE9 device,CImport::MAPS maps);
	HRESULT	Init(LPDIRECT3DDEVICE9 device,CImport::MAPS maps);

	void Scroll(float scroll);

private:
	CBackground* m_top;		// 背景リスト先頭
	CBackground* m_cur;		// 背景リスト末尾
};

//=============================================================================
#endif
