//*****************************************************************************
//
// CPhaseクラス [phase.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "phase.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CFade*			CPhase::m_fade		= NULL;
CSound*			CPhase::m_sound		= NULL;
CInputKeyboard*	CPhase::m_keyboard	= NULL;
CInputPadX*		CPhase::m_padX		= NULL;
