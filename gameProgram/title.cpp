//*****************************************************************************
//
// CTitleクラス [title.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

#include "equipment_choice.h"
#include "stage_select.h"

#include "inputKeyboard.h"
#include "inputPadX.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTitle::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// デバイス取得
	//----------------------------
	m_device = device;

	//----------------------------
	// オブジェクト
	//----------------------------
	InitObject(device);

	//----------------------------
	// フェード
	//----------------------------
	m_fade = CFade::Create(device);
	m_fade->Start(CFade::FADESTATE_IN, 1, 1.0f, 1.0f, 1.0f, 1.0f);

	//----------------------------
	// サウンドの再生
	//----------------------------
	m_sound->Play(CSound::SOUND_LABEL_TITLEBGM);

	// ステータス初期化
	m_time = 0;
	move = 0;
	cur = 0;

	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CTitle::Uninit(void)
{
	//----------------------------
	// オブジェクト
	//----------------------------
	// シーン
	CScene::ReleaseAll();

	//----------------------------
	// サウンドの停止
	//----------------------------
	m_sound->Stop(CSound::SOUND_LABEL_TITLEBGM);
}

//=============================================================================
// 更新
//=============================================================================
void CTitle::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//----------------------------
		// 入力
		//----------------------------
		if(m_keyboard->GetTrigger(DIK_RETURN))
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
			m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECT_ENTERSE);
		}

		if(m_padX != NULL)
		{
			if(m_padX->GetButtonPress(XINPUT_GAMEPAD_A))
			{
				m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
				m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECT_ENTERSE);
			}
		}


		if(m_keyboard->GetTrigger(DIK_S))
		{
			if(cur == 0)
			{
				cur = 1;
				titleButton[0]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
				titleButton[0]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
				titleButton[0]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
				titleButton[0]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
				titleButton[0]->SetSize((titleButton[0]->GetSize() / 12) * 10);

				titleButton[1]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
				titleButton[1]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
				titleButton[1]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
				titleButton[1]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
				titleButton[1]->SetSize(titleButton[1]->GetSize() * 1.2f);
				m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECTSE);
			}
		}
		else if(m_keyboard->GetTrigger(DIK_W))
		{
			if(cur == 1)
			{
				cur = 0;
				titleButton[0]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
				titleButton[0]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
				titleButton[0]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
				titleButton[0]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
				titleButton[0]->SetSize(titleButton[0]->GetSize() * 1.2f);

				titleButton[1]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
				titleButton[1]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
				titleButton[1]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
				titleButton[1]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
				titleButton[1]->SetSize((titleButton[1]->GetSize() / 12) * 10);
				m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECTSE);
			}
		}

		if(m_padX != NULL)
		{
			if(m_padX->GetButtonPress(XINPUT_GAMEPAD_DPAD_DOWN))
			{
				if(cur == 0)
				{
					cur = 1;
					titleButton[0]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
					titleButton[0]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
					titleButton[0]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
					titleButton[0]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
					titleButton[0]->SetSize((titleButton[0]->GetSize() / 12) * 10);

					titleButton[1]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
					titleButton[1]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
					titleButton[1]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
					titleButton[1]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
					titleButton[1]->SetSize(titleButton[1]->GetSize() * 1.2f);
					m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECTSE);
				}
			}

			if(m_padX->GetButtonPress(XINPUT_GAMEPAD_DPAD_UP))
			{
				if(cur == 1)
				{
					cur = 0;
					titleButton[0]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
					titleButton[0]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
					titleButton[0]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
					titleButton[0]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
					titleButton[0]->SetSize(titleButton[0]->GetSize() * 1.2f);

					titleButton[1]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
					titleButton[1]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
					titleButton[1]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
					titleButton[1]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
					titleButton[1]->SetSize((titleButton[1]->GetSize() / 12) * 10);
					m_sound->Play(CSound::SOUND_LABEL_SYSTEM_SELECTSE);
				}
			}
		}

		//揺れ時間を増やす
		m_time += SHAKING_SPD/2;
		//sinを使ってrot値検出
		float value = sinf(m_time) * SHAKING_WIDTH/2;
		//揺らす
		titleLogo->SetRot(value);
	}

	//----------------------------
	// 画面遷移
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		switch(cur)
		{
		case 0:
			CManager::SetNextPhase((CPhase*)new CStageSelect);
			break;
		case 1:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CTitle::InitObject(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// タイトル背景
	//----------------------------
	CScene2D* titleBG = CScene2D::Create(device, CImport::TITLEBG, CScene2D::POINT_CENTER);
	titleBG->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	titleBG->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//----------------------------
	// タイトルロゴ
	//----------------------------
	titleLogo = CScene2D::Create(device, CImport::TITLELOGO, CScene2D::POINT_CENTER);
	titleLogo->SetSize(876.0f * 0.6f, 563.0f * 0.6f);
	titleLogo->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f);

	// ボタン
	titleButton[0] = CScene2D::Create(device, CImport::BUTTON_ENTER, CScene2D::POINT_CENTER);
	titleButton[0]->SetSize(445.0f, 225.0f/3);
	titleButton[0]->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.65f);
	titleButton[0]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 2));
	titleButton[0]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 2));
	titleButton[0]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 3));
	titleButton[0]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 3));
	titleButton[0]->SetSize(titleButton[0]->GetSize() * 1.2f);

	titleButton[1] = CScene2D::Create(device, CImport::BUTTON_CLOSE, CScene2D::POINT_CENTER);
	titleButton[1]->SetSize(163.0f, 225.0f/3);
	titleButton[1]->SetPos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f);
	titleButton[1]->SetCord(0, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 0));
	titleButton[1]->SetCord(1, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 0));
	titleButton[1]->SetCord(2, D3DXVECTOR2(0.0f, (1.0f / 3.0f) * 1));
	titleButton[1]->SetCord(3, D3DXVECTOR2(1.0f, (1.0f / 3.0f) * 1));
}
