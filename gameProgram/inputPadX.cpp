//*****************************************************************************
//
// CInputPadXクラス [inputPadX.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "inputPadX.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define REPEAT_MIN		(30)	// リピート開始カウント数
#define REPEAT_BETWEEN	(3)		// リピート間隔カウント数
#define BUTTON_NUM		(14)	// ボタンの数

const WORD PAD_BUTTON[BUTTON_NUM] =
{
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y
};

//=============================================================================
// コンストラクタ
//=============================================================================
CInputPadX::CInputPadX(void)
{
	// 接続ナンバー
	m_no = -1;

	// 接続情報
	m_connected = false;

	// 入力情報
	m_state.Gamepad.wButtons		= 0;
	m_state.Gamepad.bLeftTrigger	= 0;
	m_state.Gamepad.bRightTrigger	= 0;
	m_state.Gamepad.sThumbLX		= 0;
	m_state.Gamepad.sThumbLY		= 0;
	m_state.Gamepad.sThumbRX		= 0;
	m_state.Gamepad.sThumbRY		= 0;

	m_trigger.Gamepad.wButtons		= 0;
	m_trigger.Gamepad.bLeftTrigger	= 0;
	m_trigger.Gamepad.bRightTrigger	= 0;
	m_trigger.Gamepad.sThumbLX		= 0;
	m_trigger.Gamepad.sThumbLY		= 0;
	m_trigger.Gamepad.sThumbRX		= 0;
	m_trigger.Gamepad.sThumbRY		= 0;

	m_release.Gamepad.wButtons		= 0;
	m_release.Gamepad.bLeftTrigger	= 0;
	m_release.Gamepad.bRightTrigger	= 0;
	m_release.Gamepad.sThumbLX		= 0;
	m_release.Gamepad.sThumbLY		= 0;
	m_release.Gamepad.sThumbRX		= 0;
	m_release.Gamepad.sThumbRY		= 0;

	m_repeat.Gamepad.wButtons		= 0;
	m_repeat.Gamepad.bLeftTrigger	= 0;
	m_repeat.Gamepad.bRightTrigger	= 0;
	m_repeat.Gamepad.sThumbLX		= 0;
	m_repeat.Gamepad.sThumbLY		= 0;
	m_repeat.Gamepad.sThumbRX		= 0;
	m_repeat.Gamepad.sThumbRY		= 0;
}

//=============================================================================
// 生成
//=============================================================================
CInputPadX* CInputPadX::Create(void)
{
	CInputPadX* pointer = new CInputPadX;
	pointer->Init();
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInputPadX::Init(void)
{
	//----------------------------
	// パッド接続情報取得
	//----------------------------
	XINPUT_STATE pad;

	for(DWORD cnt = 0; cnt < PAD_NUM; ++cnt)
	{
		if(XInputGetState(cnt, &pad) != ERROR_SUCCESS)
		{
			// 繋がっていない
			m_connected = false;
		}
		else
		{
			// 繋がっている
			m_no = cnt;
			m_padFlg[m_no] = true;
			m_connected	  = true;
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CInputPadX::Uninit(void)
{
	if(m_connected == true)
	{
		m_padFlg[m_no] = false;
	}
}

//=============================================================================
// 更新
//=============================================================================
void CInputPadX::Update(void)
{
	//----------------------------
	// パッド情報更新
	//----------------------------
	XINPUT_STATE pad;

	if(XInputGetState(m_no, &m_state) != ERROR_SUCCESS)
	{
		// 繋がっていない
		m_connected = false;
	}
	else
	{
		// 繋がっている
		m_connected = true;

//		//----------------------------
//		// 入力情報更新
//		//----------------------------
//		// ボタン情報
//		for(int cnt = 0; cnt < BUTTON_NUM; ++cnt)
//		{
//			// トリガー
//		}
	}
}
