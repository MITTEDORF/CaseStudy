//*****************************************************************************
//
// CInputPadX�N���X [inputPadX.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "inputPadX.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define REPEAT_MIN		(30)	// ���s�[�g�J�n�J�E���g��
#define REPEAT_BETWEEN	(3)		// ���s�[�g�Ԋu�J�E���g��
#define BUTTON_NUM		(14)	// �{�^���̐�

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
// �R���X�g���N�^
//=============================================================================
CInputPadX::CInputPadX(void)
{
	// �ڑ��i���o�[
	m_no = -1;

	// �ڑ����
	m_connected = false;

	// ���͏��
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
// ����
//=============================================================================
CInputPadX* CInputPadX::Create(void)
{
	CInputPadX* pointer = new CInputPadX;
	pointer->Init();
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CInputPadX::Init(void)
{
	//----------------------------
	// �p�b�h�ڑ����擾
	//----------------------------
	XINPUT_STATE pad;

	for(DWORD cnt = 0; cnt < PAD_NUM; ++cnt)
	{
		if(XInputGetState(cnt, &pad) != ERROR_SUCCESS)
		{
			// �q�����Ă��Ȃ�
			m_connected = false;
		}
		else
		{
			// �q�����Ă���
			m_no = cnt;
			m_padFlg[m_no] = true;
			m_connected	  = true;
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CInputPadX::Uninit(void)
{
	if(m_connected == true)
	{
		m_padFlg[m_no] = false;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CInputPadX::Update(void)
{
	//----------------------------
	// �p�b�h���X�V
	//----------------------------
	XINPUT_STATE pad;

	if(XInputGetState(m_no, &m_state) != ERROR_SUCCESS)
	{
		// �q�����Ă��Ȃ�
		m_connected = false;
	}
	else
	{
		// �q�����Ă���
		m_connected = true;

//		//----------------------------
//		// ���͏��X�V
//		//----------------------------
//		// �{�^�����
//		for(int cnt = 0; cnt < BUTTON_NUM; ++cnt)
//		{
//			// �g���K�[
//		}
	}
}
