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
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BUTTON_NUM	(14)	// ボタンの数
#define TRIGGER_NUM	(2)		// トリガーの数

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

	bool GetButtonPress(WORD wButton){return (m_state.wButtons & wButton) ? true : false;}
	bool GetLeftTriggerPress(void){return (m_state.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}
	bool GetRightriggerPress(void){return (m_state.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}

	bool GetButtonTrigger(WORD wButton){return (m_trigger.wButtons & wButton) ? true : false;}
	bool GetLeftTriggerTrigger(void){return (m_trigger.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}
	bool GetRightriggerTrigger(void){return (m_trigger.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}

	bool GetButtonRelease(WORD wButton){return (m_release.wButtons & wButton) ? true : false;}
	bool GetLeftTriggerRelease(void){return (m_release.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}
	bool GetRightriggerRelease(void){return (m_release.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;}

	SHORT GetThumbLX(void){return (abs(m_state.sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ?  m_state.sThumbLX : 0;}
	SHORT GetThumbLY(void){return (abs(m_state.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ?  m_state.sThumbLY : 0;}
	SHORT GetThumbRX(void){return (abs(m_state.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? m_state.sThumbRX : 0;}
	SHORT GetThumbRY(void){return (abs(m_state.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? m_state.sThumbRY : 0;}

private:
	bool m_connected;
	int	 m_no;

	XINPUT_GAMEPAD m_state;
	XINPUT_GAMEPAD m_trigger;
	XINPUT_GAMEPAD m_release;
	XINPUT_GAMEPAD m_repeat;

	unsigned int m_cntRepeatBtn[BUTTON_NUM];
	unsigned int m_cntRepeatTrigger[TRIGGER_NUM];
};

//=============================================================================
#endif