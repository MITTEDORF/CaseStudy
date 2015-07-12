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
#include "debugproc.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define REPEAT_MIN		(30)	// ���s�[�g�J�n�J�E���g��
#define REPEAT_BETWEEN	(3)		// ���s�[�g�Ԋu�J�E���g��

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
	m_state.wButtons		= 0;
	m_state.bLeftTrigger	= 0;
	m_state.bRightTrigger	= 0;
	m_state.sThumbLX		= 0;
	m_state.sThumbLY		= 0;
	m_state.sThumbRX		= 0;
	m_state.sThumbRY		= 0;

	m_trigger.wButtons		= 0;
	m_trigger.bLeftTrigger	= 0;
	m_trigger.bRightTrigger	= 0;
	m_trigger.sThumbLX		= 0;
	m_trigger.sThumbLY		= 0;
	m_trigger.sThumbRX		= 0;
	m_trigger.sThumbRY		= 0;

	m_release.wButtons		= 0;
	m_release.bLeftTrigger	= 0;
	m_release.bRightTrigger	= 0;
	m_release.sThumbLX		= 0;
	m_release.sThumbLY		= 0;
	m_release.sThumbRX		= 0;
	m_release.sThumbRY		= 0;

	m_repeat.wButtons		= 0;
	m_repeat.bLeftTrigger	= 0;
	m_repeat.bRightTrigger	= 0;
	m_repeat.sThumbLX		= 0;
	m_repeat.sThumbLY		= 0;
	m_repeat.sThumbRX		= 0;
	m_repeat.sThumbRY		= 0;

	// ���s�[�g�J�E���g
	for(int cnt = 0; cnt < BUTTON_NUM; ++cnt)
	{
		m_cntRepeatBtn[cnt] = 0;
	}
	for(int cnt = 0; cnt < TRIGGER_NUM; ++cnt)
	{
		m_cntRepeatTrigger[cnt] = 0;
	}
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
	XINPUT_STATE	pad;

	if(XInputGetState(m_no, &pad) != ERROR_SUCCESS)
	{
		// �q�����Ă��Ȃ�
		m_connected = false;
	}
	else
	{
		// �q�����Ă���
		m_connected = true;

		//----------------------------
		// ���͏��X�V
		//----------------------------
		XINPUT_GAMEPAD padInput = pad.Gamepad;

		// �g���K�[
		m_trigger.wButtons		= (padInput.wButtons	  ^ m_state.wButtons)		& padInput.wButtons;
		m_trigger.bLeftTrigger	= (padInput.bLeftTrigger  ^ m_state.bLeftTrigger)	& padInput.bLeftTrigger;
		m_trigger.bRightTrigger	= (padInput.bRightTrigger ^ m_state.bRightTrigger)	& padInput.bRightTrigger;
		m_trigger.sThumbLX		= (padInput.sThumbLX	  ^ m_state.sThumbLX)		& padInput.sThumbLX;
		m_trigger.sThumbLY		= (padInput.sThumbLY	  ^ m_state.sThumbLY)		& padInput.sThumbLY;
		m_trigger.sThumbRX		= (padInput.sThumbRX	  ^ m_state.sThumbRX)		& padInput.sThumbRX;
		m_trigger.sThumbRY		= (padInput.sThumbRY	  ^ m_state.sThumbRY)		& padInput.sThumbRY;

		// �����[�X
		m_release.wButtons		= (padInput.wButtons	  ^ m_state.wButtons)		& m_state.wButtons;
		m_release.bLeftTrigger	= (padInput.bLeftTrigger  ^ m_state.bLeftTrigger)	& m_state.bLeftTrigger;
		m_release.bRightTrigger	= (padInput.bRightTrigger ^ m_state.bRightTrigger)	& m_state.bRightTrigger;
		m_release.sThumbLX		= (padInput.sThumbLX	  ^ m_state.sThumbLX)		& m_state.sThumbLX;
		m_release.sThumbLY		= (padInput.sThumbLY	  ^ m_state.sThumbLY)		& m_state.sThumbLY;
		m_release.sThumbRX		= (padInput.sThumbRX	  ^ m_state.sThumbRX)		& m_state.sThumbRX;
		m_release.sThumbRY		= (padInput.sThumbRY	  ^ m_state.sThumbRY)		& m_state.sThumbRY;

		// ���s�[�g
/*		for(int cnt = 0; cnt < BUTTON_NUM; ++cnt)
		{
			if(padInput.wButtons & PAD_BUTTON[cnt])
			{
				// �J�E���g�A�b�v�E�L�[���Z�b�g
			}
		}
		m_repeat.wButtons		= (padInput.wButtons	  ^ m_state.wButtons)		& m_state.wButtons;
		m_repeat.bLeftTrigger	= (padInput.bLeftTrigger  ^ m_state.bLeftTrigger)	& m_state.bLeftTrigger;
		m_repeat.bRightTrigger	= (padInput.bRightTrigger ^ m_state.bRightTrigger)	& m_state.bRightTrigger;
		m_repeat.sThumbLX		= (padInput.sThumbLX	  ^ m_state.sThumbLX)		& m_state.sThumbLX;
		m_repeat.sThumbLY		= (padInput.sThumbLY	  ^ m_state.sThumbLY)		& m_state.sThumbLY;
		m_repeat.sThumbRX		= (padInput.sThumbRX	  ^ m_state.sThumbRX)		& m_state.sThumbRX;
		m_repeat.sThumbRY		= (padInput.sThumbRY	  ^ m_state.sThumbRY)		& m_state.sThumbRY;*/

		// �v���X
		m_state = padInput;
	}

	if(CDebugproc::GetDrawFrag())
	{
		if(m_connected == true)
		{
			// �p�b�h�\�����X�V
			CDebugproc::PrintDebugProc("***�p�b�hNo:%1d******\n", m_no);
			CDebugproc::PrintDebugProc("StickL X:%d Y:%d StickR X:%d Y:%d\n",
										GetThumbLX(),
										GetThumbLY(),
										GetThumbRX(),
										GetThumbRY());

			CDebugproc::PrintDebugProc("---Press---\n", m_no);
			CDebugproc::PrintDebugProc("��:%d ��:%d ��:%d �E:%d | A:%d B:%d X:%d Y:%d\n",
										GetButtonPress(XINPUT_GAMEPAD_DPAD_UP),
										GetButtonPress(XINPUT_GAMEPAD_DPAD_DOWN),
										GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT),
										GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT),
										GetButtonPress(XINPUT_GAMEPAD_A),
										GetButtonPress(XINPUT_GAMEPAD_B),
										GetButtonPress(XINPUT_GAMEPAD_X),
										GetButtonPress(XINPUT_GAMEPAD_Y));
			CDebugproc::PrintDebugProc("L1:%d R1:%d L2:%d R2:%d L3:%d R3:%d | start:%d back:%d\n",
										GetButtonPress(XINPUT_GAMEPAD_LEFT_SHOULDER),
										GetButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER),
										GetLeftTriggerPress(),
										GetRightriggerPress(),
										GetButtonPress(XINPUT_GAMEPAD_LEFT_THUMB),
										GetButtonPress(XINPUT_GAMEPAD_RIGHT_THUMB),
										GetButtonPress(XINPUT_GAMEPAD_START),
										GetButtonPress(XINPUT_GAMEPAD_BACK));

			CDebugproc::PrintDebugProc("---Trigger---\n", m_no);
			CDebugproc::PrintDebugProc("��:%d ��:%d ��:%d �E:%d | A:%d B:%d X:%d Y:%d\n",
										GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP),
										GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN),
										GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT),
										GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT),
										GetButtonTrigger(XINPUT_GAMEPAD_A),
										GetButtonTrigger(XINPUT_GAMEPAD_B),
										GetButtonTrigger(XINPUT_GAMEPAD_X),
										GetButtonTrigger(XINPUT_GAMEPAD_Y));
			CDebugproc::PrintDebugProc("L1:%d R1:%d L2:%d R2:%d L3:%d R3:%d | start:%d back:%d\n",
										GetButtonTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER),
										GetButtonTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER),
										GetLeftTriggerTrigger(),
										GetRightriggerTrigger(),
										GetButtonTrigger(XINPUT_GAMEPAD_LEFT_THUMB),
										GetButtonTrigger(XINPUT_GAMEPAD_RIGHT_THUMB),
										GetButtonTrigger(XINPUT_GAMEPAD_START),
										GetButtonTrigger(XINPUT_GAMEPAD_BACK));

			CDebugproc::PrintDebugProc("---Release---\n", m_no);
			CDebugproc::PrintDebugProc("��:%d ��:%d ��:%d �E:%d | A:%d B:%d X:%d Y:%d\n",
										GetButtonRelease(XINPUT_GAMEPAD_DPAD_UP),
										GetButtonRelease(XINPUT_GAMEPAD_DPAD_DOWN),
										GetButtonRelease(XINPUT_GAMEPAD_DPAD_LEFT),
										GetButtonRelease(XINPUT_GAMEPAD_DPAD_RIGHT),
										GetButtonRelease(XINPUT_GAMEPAD_A),
										GetButtonRelease(XINPUT_GAMEPAD_B),
										GetButtonRelease(XINPUT_GAMEPAD_X),
										GetButtonRelease(XINPUT_GAMEPAD_Y));
			CDebugproc::PrintDebugProc("L1:%d R1:%d L2:%d R2:%d L3:%d R3:%d | start:%d back:%d\n",
										GetButtonRelease(XINPUT_GAMEPAD_LEFT_SHOULDER),
										GetButtonRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER),
										GetLeftTriggerRelease(),
										GetRightriggerRelease(),
										GetButtonRelease(XINPUT_GAMEPAD_LEFT_THUMB),
										GetButtonRelease(XINPUT_GAMEPAD_RIGHT_THUMB),
										GetButtonRelease(XINPUT_GAMEPAD_START),
										GetButtonRelease(XINPUT_GAMEPAD_BACK));
		}
	}
}
