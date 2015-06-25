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
	//プレイヤーの生成
	m_player=CPlayer::Create(device);
	m_player->SetPos(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.3f);
	m_player->SetSize(128.0f*2.f,128.0f*2.f);
	m_player->Assy_()->SetSize(m_player->GetSize());
	m_player->SetKeyboard(m_keyboard);
	m_player->Set_isGame(false);
}

//=============================================================================
// 乗り物の選択
//=============================================================================
void CEquipmentChoice::VehicleChoice()
{
	if(m_keyboard->GetTrigger(DIK_UP))
	{
		vehicle_id++;
		if(vehicle_id>=VEHICLE_MAX-1)
		{
			vehicle_id=VEHICLE_MAX-1;
		}
		m_player->SetVehicleID((VehicleID)vehicle_id);
	}

	else if(m_keyboard->GetTrigger(DIK_DOWN))
	{
		vehicle_id--;
		if(vehicle_id<=VEHICLE_TRAM)
		{
			vehicle_id=VEHICLE_TRAM;
		}
		m_player->SetVehicleID((VehicleID)vehicle_id);
	}
}
//=============================================================================
// コスチュームの選択
//=============================================================================
void CEquipmentChoice::CostumeChoice()
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