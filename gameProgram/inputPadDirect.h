//*****************************************************************************
//
// CInputPadXクラス [inputPadX.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_INPUT_PAD_DIRECT_H
#define _MY_INPUT_PAD_DIRECT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "input.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CInputPadDirect : public CInput
{
public:

	// 入力種別
	typedef enum
	{
		PAD_LS_LEFT = 0,
		PAD_LS_RIGHT,
		PAD_LS_UP,
		PAD_LS_DOWN,
		PAD_RS_LEFT,
		PAD_RS_RIGHT,
		PAD_RS_UP,
		PAD_RS_DOWN,
		PAD_BUTTON_1,		// X
		PAD_BUTTON_2,		// Y
		PAD_BUTTON_3,		// A
		PAD_BUTTON_4,		// B
		PAD_BUTTON_5,		// L1
		PAD_BUTTON_6,		// R1
		PAD_BUTTON_7,		// L2
		PAD_BUTTON_8,		// R2
		PAD_BUTTON_9,		// L3
		PAD_BUTTON_10,		// R3
		PAD_BUTTON_11,		// SELECT
		PAD_BUTTON_12,		// START
		PAD_BUTTON_13,		// PS
		PAD_MAX
	}INPUT_PAD;



	CInputPadDirect();
	~CInputPadDirect(){};

	static	CInputPadDirect* Create(void);
	HRESULT	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	// 入力判定
	bool CheckPress(int pad){ return m_press[pad]; }
	bool CheckTrigger(int pad){ return m_trigger[pad]; }
	bool CheckRepeat(int pad){ return m_repeat[pad]; }
	bool CheckRelease(int pad){ return m_release[pad]; }


private:
	// 入力コールバック関数
	static BOOL CALLBACK CallBackPad(const DIDEVICEINSTANCE *instance, VOID *reference);
	static BOOL CALLBACK CallBackAces(const LPCDIDEVICEOBJECTINSTANCE instance, LPVOID reference);
	static LPDIRECTINPUTDEVICE8	m_input_device;	// 入力処理のデバイスへのポインタ

	bool		 m_connected;
	int			 m_no;
	DIJOYSTATE2 m_joystate;
	static bool m_state[PAD_MAX];
	static bool m_press[PAD_MAX];
	static bool m_trigger[PAD_MAX];
	static bool m_repeat[PAD_MAX];
	static bool m_release[PAD_MAX];
	static int	m_repeatcount[PAD_MAX];

};

//=============================================================================
#endif