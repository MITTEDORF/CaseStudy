//*****************************************************************************
//
// CInputPadDirectクラス [inputPadX.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "inputPadDirect.h"
#include "manager.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PAD_STICK_INPUTLANGE	( 32 )

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// スタティック変数宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTINPUTDEVICE8 CInputPadDirect::m_input_device;
bool CInputPadDirect::m_state[PAD_MAX];
bool CInputPadDirect::m_press[PAD_MAX];
bool CInputPadDirect::m_trigger[PAD_MAX];
bool CInputPadDirect::m_repeat[PAD_MAX];
bool CInputPadDirect::m_release[PAD_MAX];
int	 CInputPadDirect::m_repeatcount[PAD_MAX];


//=============================================================================
// コンストラクタ
//=============================================================================
CInputPadDirect::CInputPadDirect(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CInputPadDirect* CInputPadDirect::Create(void)
{
	CInputPadDirect* pointer = new CInputPadDirect;
	pointer->Init();
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInputPadDirect::Init(void)
{
	//----------------------------
	// 変数宣言
	//----------------------------
	HRESULT result;

	//----------------------------
	// デバイス生成
	//----------------------------
	result = m_input->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		CallBackPad,
		NULL,
		DIEDFL_ATTACHEDONLY);

	// エラーチェック
	if (FAILED(result) || m_input_device == NULL)
	{
		return E_FAIL;
	}
	
	//----------------------------
	// デバイス情報設定
	//----------------------------
	result = m_input_device->SetDataFormat(&c_dfDIJoystick2);

	// エラーチェック
	if (FAILED(result))
	{
		return E_FAIL;
	}

	//----------------------------
	// デバイス協調レベルを設定
	//----------------------------
	result = m_input_device->SetCooperativeLevel(CManager::GetWindowHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// エラーチェック
	if (FAILED(result))
	{
		return E_FAIL;
	}

	//----------------------------
	// 使用可能なデバイスの検索
	//----------------------------
	result = m_input_device->EnumObjects(CallBackAces, NULL, DIDFT_AXIS);

	// エラーチェック
	if (FAILED(result))
	{
		return E_FAIL;
	}

	// 入力許可の要求
	m_input_device->Acquire();

	// ワークを生成
	memset(&m_joystate, 0, sizeof(m_joystate));
	memset(&m_press, 0, sizeof(m_press));
	memset(&m_trigger, 0, sizeof(m_trigger));
	memset(&m_repeat, 0, sizeof(m_repeat));
	memset(&m_release, 0, sizeof(m_release));

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CInputPadDirect::Uninit(void)
{
	// パッド用デバイスの破棄
	if (m_input_device)
	{
		m_input_device->Unacquire();
		m_input_device->Release();
		m_input_device = NULL;
	}
}

//=============================================================================
// 更新
//=============================================================================
void CInputPadDirect::Update(void)
{

	// 変数宣言
	bool State[PAD_MAX];


	// デバイス生成確認
	if (m_input_device == NULL)
	{
		return;
	}


	// デバイスからステータスを取得
	if (SUCCEEDED(m_input_device->GetDeviceState(sizeof(m_joystate), &m_joystate)))
	{

		for (int nPad = 0, nCnt = 0; nPad + nCnt < PAD_MAX; nPad++)
		{
			// アナログスティック
			if (nPad == 0)
			{
				State[PAD_LS_LEFT] = m_joystate.lX < -PAD_STICK_INPUTLANGE || (m_joystate.rgdwPOV[0] >= 225 * 100 && m_joystate.rgdwPOV[0] <= 315 * 100);
				State[PAD_LS_RIGHT] = m_joystate.lX > PAD_STICK_INPUTLANGE || (m_joystate.rgdwPOV[0] >= 45 * 100 && m_joystate.rgdwPOV[0] <= 135 * 100);
				State[PAD_LS_UP] = m_joystate.lY < -PAD_STICK_INPUTLANGE || ((m_joystate.rgdwPOV[0] >= 315 * 100 && m_joystate.rgdwPOV[0] <= 360 * 100) || (m_joystate.rgdwPOV[0] >= 0 * 100 && m_joystate.rgdwPOV[0] <= 45 * 100));
				State[PAD_LS_DOWN] = m_joystate.lY > PAD_STICK_INPUTLANGE || (m_joystate.rgdwPOV[0] >= 135 * 100 && m_joystate.rgdwPOV[0] <= 225 * 100);

				State[PAD_RS_LEFT] = m_joystate.lZ < -PAD_STICK_INPUTLANGE;
				State[PAD_RS_RIGHT] = m_joystate.lZ > PAD_STICK_INPUTLANGE;
				State[PAD_RS_UP] = m_joystate.lRz < -PAD_STICK_INPUTLANGE;
				State[PAD_RS_DOWN] = m_joystate.lRz > PAD_STICK_INPUTLANGE;

				nCnt = 8;
			}

			State[nPad + nCnt] = m_joystate.rgbButtons[nPad] == 128;
		}

		for (int nPad = 0; nPad < PAD_MAX; nPad++)
		{
			m_trigger[nPad] = (State[nPad] ^ m_state[nPad]) & State[nPad];
			m_release[nPad] = (State[nPad] ^ m_state[nPad]) & m_state[nPad];
			m_press[nPad] = State[nPad];

			// PadState Regist
			m_state[nPad] = State[nPad];

		}
	}

	// デバイスステータスを取得できていなかったら再要求
	else
	{
		m_input_device->Acquire();
	}

}

//=============================================================================
// デバイスオブジェクトのコールバック関数
//=============================================================================
BOOL CALLBACK CInputPadDirect::CallBackPad(const DIDEVICEINSTANCE *lpddi, VOID *pvRef)
{
	// 変数宣言
	DIDEVCAPS	DevCaps;
	HRESULT		Result;

	// ジョイパッド用デバイスの生成
	Result = m_input->CreateDevice(lpddi->guidInstance, &m_input_device, NULL);

	// エラーチェック
	if (FAILED(Result))
	{
		return DIENUM_CONTINUE;
	}

	// パッドのステータスを検索
	DevCaps.dwSize = sizeof(DIDEVCAPS);
	Result = m_input_device->GetCapabilities(&DevCaps);

	// エラーチェック
	if (FAILED(Result))
	{
		m_input_device->Release();
		m_input_device = NULL;
		return DIENUM_CONTINUE;
	}

	// リターン
	return DIENUM_STOP;
}


//=============================================================================
// デバイスのコールバック関数
//=============================================================================
BOOL CALLBACK CInputPadDirect::CallBackAces(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	// 変数宣言
	HRESULT Result;

	// アナログスティックの深度値を設定
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -1000;
	diprg.lMax = 1000;


	// プロパティ設定
	Result = m_input_device->SetProperty(DIPROP_RANGE, &diprg.diph);

	// エラーチェック
	if (FAILED(Result))
	{
		return DIENUM_STOP;
	}

	// リターン
	return DIENUM_CONTINUE;

}
