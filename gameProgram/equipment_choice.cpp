//*****************************************************************************
//
// 装備選択画面制御クラス [equipment_choice.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "equipment_choice.h"
#include "manager.h"
#include "fade.h"

#include "game.h"

#include "inputKeyboard.h"

#include "character_player.h"

#include "math_animation.h"

#include "equipment_choice_config.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// 初期化
//=============================================================================
HRESULT CEquipmentChoice::Init(LPDIRECT3DDEVICE9 device)
{
	//変数のNULL埋め
	NullSetVariable();
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
	// バージョン表示
	//----------------------------
	m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);

	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CEquipmentChoice::Uninit(void)
{
	//----------------------------
	// オブジェクト
	//----------------------------
	// シーン
	CScene::ReleaseAll();
}

//=============================================================================
// 更新
//=============================================================================
void CEquipmentChoice::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		CostumeChoice();
		VehicleChoice();
		CurUpdate();
		AnimUpdate();
		cosUpdate();
		//----------------------------
		// 入力
		//----------------------------
		if(m_keyboard->GetTrigger(DIK_RETURN))
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

	//----------------------------
	// 画面遷移
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		CManager::SetNextPhase((CPhase*)new CGame((CostumeID)costume_id,(VehicleID)vehicle_id));
	}

	// 背景スクロール処理
	D3DXVECTOR2 tmp;
	float scroll = 0.002;
	for(int i = 0; i < 4;  i++)
	{
		tmp = m_bg->GetCord(i);
		tmp.y -= scroll;
		m_bg->SetCord(i, tmp);
	}
}

//=============================================================================
// 描画
//=============================================================================
void CEquipmentChoice::Draw(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CEquipmentChoice::InitObject(LPDIRECT3DDEVICE9 device)
{
	// 背景
	CScene2D* bg = CScene2D::Create(device, CImport::MAKE_UI_CHAR_SEL_BACK_01, CScene2D::POINT_LEFTTOP, 1);
	bg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	bg->SetPos(0.0f, 0.0f);

	// スクロールする背景
	m_bg = CScene2D::Create(device, CImport::MAKE_UI_CHAR_SEL_CHIP_01, CScene2D::POINT_CENTER, 2);
	m_bg->SetSize(SCREEN_WIDTH * 1.3, SCREEN_WIDTH * 1.3);
	m_bg->SetPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_bg->SetRot(-0.5f);

	//プレイヤーの生成
	m_player=CPlayer::Create(device);
	m_player->SetPos(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f);
	m_player->SetSize(128.0f*2.5f,128.0f*2.5f);
	m_player->Assy_()->SetSize(m_player->GetSize());
	m_player->SetKeyboard(m_keyboard);
	m_player->Set_isGame(false);

	m_cos=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cos);

	m_ass=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass->SetPos(SCREEN_WIDTH * 0.3f, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass);

	m_cur=CScene2D::Create(device, CImport::MAKE_UI_SELECT_CUR, CScene2D::POINT_CENTER);
	m_cur->SetSize(320.f,210.f);
	m_cur->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cur);

	m_slotback=CScene2D::Create(device, CImport::MAKE_UI_SELECT_FRAME, CScene2D::POINT_CENTER);
	m_slotback->SetSize(721.f,496.f);
	m_slotback->SetPos(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f);

	// 効果テキスト
	m_message = CScene2D::Create(device, CImport::MAKE_UI_VEH_MES_SLED, CScene2D::POINT_CENTER);
	m_message->SetSize(1200.0f,91.0f);
	m_message->SetPos(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9);
	// 効果ウィンドウ
	m_message_win = CScene2D::Create(device, CImport::MAKE_UI_COS_DETAIL, CScene2D::POINT_CENTER,2);
	m_message_win->SetSize(1200.0f,91.0f);
	m_message_win->SetPos(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9);

	// 乗り物名テキスト
	m_veh_mes = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_5, CScene2D::POINT_CENTER);
	m_veh_mes->SetSize(466.0f,91.0f);
	m_veh_mes->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55);
	// 乗り物名ウィンドウ
	m_veh_mes_win = CScene2D::Create(device, CImport::MAKE_UI_ASSY_OPTION, CScene2D::POINT_CENTER,2);
	m_veh_mes_win->SetSize(466.0f,91.0f);
	m_veh_mes_win->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55);

	// 服装テキスト
	m_cos_mes = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_5, CScene2D::POINT_CENTER);
	m_cos_mes->SetSize(466.0f,91.0f);
	m_cos_mes->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55 + 91.0f);
	// 服装ウィンドウ
	m_cos_mes_win = CScene2D::Create(device, CImport::MAKE_UI_COS_OPTION, CScene2D::POINT_CENTER,2);
	m_cos_mes_win->SetSize(466.0f,91.0f);
	m_cos_mes_win->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55 + 91.0f);
}

//=============================================================================
// 乗り物の選択
//=============================================================================
void CEquipmentChoice::VehicleChoice()
{
	if(m_cur->GetPos().y==CUR_BUTTOM)
	{
		if(m_keyboard->GetTrigger(DIK_LEFT))
		{
			vehicle_id--;
			if(vehicle_id<=VEHICLE_TRAM)
			{
				vehicle_id=VEHICLE_TRAM;
			}
			m_player->SetVehicleID((VehicleID)vehicle_id);
		}

		else if(m_keyboard->GetTrigger(DIK_RIGHT))
		{
			vehicle_id++;
			if(vehicle_id>=VEHICLE_MAX-1)
			{
				vehicle_id=VEHICLE_MAX-1;
			}
			m_player->SetVehicleID((VehicleID)vehicle_id);
		}
	}
}
//=============================================================================
// コスチュームの選択
//=============================================================================
void CEquipmentChoice::CostumeChoice()
{
	if(m_cur->GetPos().y==CUR_UP)
	{
		if(m_keyboard->GetTrigger(DIK_LEFT))
		{
			costume_id--;
			if(costume_id<=COSTUME_NONE)
			{
				costume_id=COSTUME_NONE;
			}
			m_player->SetCostumeID((CostumeID)costume_id);
		}

		else if(m_keyboard->GetTrigger(DIK_RIGHT))
		{
			costume_id++;
			if(costume_id>=COSTUME_MAX-1)
			{
				costume_id=COSTUME_MAX-1;
			}
			m_player->SetCostumeID((CostumeID)costume_id);
		}
	}
}

void CEquipmentChoice::AnimUpdate()
{
	if(cntAnim>=10)
		{
			nowAnim++;
			if(nowAnim==5)
			{
				nowAnim=1;
			}

			SetAnim(4,nowAnim,1,1,m_cur);
			cntAnim=0;
		}
		cntAnim++;
}

void CEquipmentChoice::CurUpdate()
{
	if(m_keyboard->GetTrigger(DIK_UP))
	{
		m_cur->SetPosY(CUR_UP);
	}

	else if(m_keyboard->GetTrigger(DIK_DOWN))
	{
		m_cur->SetPosY(CUR_BUTTOM);
	}
}

void CEquipmentChoice::cosUpdate()
{
	m_cos->SetTex(m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT));
	m_ass->SetTex(m_player->ConsultationVehicleTexID());
}