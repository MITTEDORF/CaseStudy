//*****************************************************************************
//
// CInputPadXクラス [inputPadX.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_INPUT_PADX_H
#define _MY_INPUT_PADX_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "input.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CInputPadX : public CInput
{
public:
	CInputPadX();
	~CInputPadX(){};

	static	CInputPadX* Create(void);
	HRESULT	Init(void);
	void	Uninit(void);
	void	Update(void);

	bool GetPadFlg(void){return (m_no < 0) ? false : true;}

	bool GetButton(WORD wButton){return (m_state.Gamepad.wButtons & wButton) ? true : false;}
	bool GetLeftTrigger(void){return (m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}
	bool GetRightrigger(void){return (m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}

	SHORT GetThumbLX(void){return (abs(m_state.Gamepad.sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ?  m_state.Gamepad.sThumbLX : 0;}
	SHORT GetThumbLY(void){return (abs(m_state.Gamepad.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ?  m_state.Gamepad.sThumbLY : 0;}
	SHORT GetThumbRX(void){return (abs(m_state.Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? m_state.Gamepad.sThumbRX : 0;}
	SHORT GetThumbRY(void){return (abs(m_state.Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? m_state.Gamepad.sThumbRY : 0;}

private:
	bool		 m_connected;
	int			 m_no;

	XINPUT_STATE m_state;
	XINPUT_STATE m_trigger;
	XINPUT_STATE m_release;
	XINPUT_STATE m_repeat;
};

//=============================================================================
#endif