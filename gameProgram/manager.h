//*****************************************************************************
//
// CManagerクラス [manager.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_MANAGER_H
#define _MY_MANAGER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CRenderer;
class CDebugproc;
class CImport;
class CPhase;
class CNLoad;
class CInputKeyboard;
class CInputPadX;
class CThread;
class CManager
{
public:
	CManager();
	~CManager(){};

	static	CManager* Create(HINSTANCE instance, HWND wnd, bool window);
	HRESULT	Init(HINSTANCE instance, HWND wnd, bool window);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void	CalculateFPS(DWORD frameCnt, DWORD curTime, DWORD FPSLastTime);

	static void SetNextPhase(CPhase* phase){m_phaseNext = phase;}
	static HWND GetWindowHandle(){ return m_window_handle; }

private:
	void Change( void );
	static void Load( void );
	static void InitLoad( void );
	static HWND m_window_handle;

	static CRenderer*	m_renderer;
	CDebugproc*	m_debugproc;
	CImport*	m_import;

	static CPhase*	m_phase;
	static CPhase*	m_phaseNext;
	static CNLoad*	m_now_load;
	CInputKeyboard*	m_keyboard;
	CInputPadX*		m_padX;
	static bool m_loading_flag;
	static CThread* m_Thread;
};

//=============================================================================
#endif