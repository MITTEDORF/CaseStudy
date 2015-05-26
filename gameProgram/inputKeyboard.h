//*****************************************************************************
//
// CInputKeyboardクラス [inputKeyboard.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_INPUT_KEYBOARD_H
#define _MY_INPUT_KEYBOARD_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "input.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define KEYBOARD_MAX	(256)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard(){};

	static	CInputKeyboard* Create(HINSTANCE instance, HWND wnd);
	HRESULT	Init(HINSTANCE instance, HWND wnd);
	void	Uninit(void);
	void	Update(void);

	static bool GetPress(int key){return (m_state[key] & 0x80) ? true : false;}
	static bool GetTrigger(int key){return (m_trigger[key] & 0x80) ? true : false;}
	static bool GetSetDelete(int key){return (m_release[key] & 0x80) ? true : false;}
	static bool GetRepeat(int key){return (m_repeat[key] & 0x80) ? true : false;}

private:
	LPDIRECTINPUTDEVICE8	m_inputDevice;	// 入力処理のデバイスへのポインタ

	static BYTE m_state[KEYBOARD_MAX];
	static BYTE m_trigger[KEYBOARD_MAX];
	static BYTE m_release[KEYBOARD_MAX];
	static BYTE m_repeat[KEYBOARD_MAX];

	unsigned int m_cntRepeat[KEYBOARD_MAX];
};

//=============================================================================
#endif