//*****************************************************************************
//
// CRendererクラス [renderer.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_RENDERER_H
#define _MY_RENDERER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CDebugproc;

class CRenderer
{
public:
	CRenderer();
	~CRenderer(){};

	static	CRenderer* Create(HWND wnd, bool window);
	HRESULT	Init(HWND wnd, bool window);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void){return m_device;}
	void SetDebugproc(CDebugproc* debugproc){m_debugproc = debugproc;}

	void SetFPS(int fps){m_countFPS = fps;}
	int  GetFPS(void){return m_countFPS;}

	static void ScreenShot(
		D3DXIMAGE_FILEFORMAT format,
		RECT rect);

private:
	LPDIRECT3DDEVICE9	m_device;
	CDebugproc*			m_debugproc;

	static LPDIRECT3DSURFACE9 m_screenshot_surface;

	int	 m_countFPS;
};

//=============================================================================
#endif