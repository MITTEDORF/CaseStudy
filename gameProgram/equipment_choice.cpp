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
#include "character_config.h"
#include "configholder.h"

#include "sound.h"

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

	cosUpdate(0);
	cosUpdate(1);
	cosUpdate(2);

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

		cosUpdate(0);
		cosUpdate(1);
		cosUpdate(2);

		//----------------------------
		// 入力
		//----------------------------
		if(m_keyboard->GetTrigger(DIK_RETURN))
		{
			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

	//----------------------------
	// 画面遷移
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		CConfigHolder::Set(CONFIG_COSTUME,costume_id);
		CConfigHolder::Set(CONFIG_ASSY,vehicle_id);
		CManager::SetNextPhase((CPhase*)new CGame());
	}

	// 背景スクロール処理
	D3DXVECTOR2 tmp;
	float scroll = 0.002f;
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

	CScene2D* mes = CScene2D::Create(device, CImport::SEL_COS, CScene2D::POINT_CENTER, 3);
	mes->SetSize(940.0f, 46.0f);
	mes->SetPos(SCREEN_WIDTH/2, 40.0f);

	// スクロールする背景
	m_bg = CScene2D::Create(device, CImport::MAKE_UI_CHAR_SEL_CHIP_01, CScene2D::POINT_CENTER, 2);
	m_bg->SetSize(SCREEN_WIDTH * 1.3, SCREEN_WIDTH * 1.3);
	m_bg->SetPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_bg->SetRot(-0.5f);

	//プレイヤーの生成
	m_player=CPlayer::Create(device);
	m_player->SetPos(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.3f);
	m_player->SetSize(128.0f*2.0f,128.0f*2.0f);
	m_player->Assy_()->SetSize(m_player->GetSize());
	m_player->SetKeyboard(m_keyboard);
	m_player->Set_isGame(false);

	float PolSize=m_player->GetSize().x/1.5f;

	m_cos[0]=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos[0]->SetPos(SCREEN_WIDTH * 0.3f-PolSize, CUR_UP);
	SetAnim(4,1,1,1,m_cos[0]);

	m_ass[0]=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass[0]->SetPos(SCREEN_WIDTH * 0.3f-PolSize, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass[0]);

	m_cos[1]=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos[1]->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cos[1]);

	m_ass[1]=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass[1]->SetPos(SCREEN_WIDTH * 0.3f, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass[1]);

	m_cos[2]=CScene2D::Create(device, CImport::PLAYER_DEFAULT_WAIT, CScene2D::POINT_CENTER);
	m_cos[2]->SetPos(SCREEN_WIDTH * 0.3f+PolSize, CUR_UP);
	SetAnim(4,1,1,1,m_cos[2]);

	m_ass[2]=CScene2D::Create(device, CImport::ASSY_TRAM, CScene2D::POINT_CENTER);
	m_ass[2]->SetPos(SCREEN_WIDTH * 0.3f+PolSize, CUR_BUTTOM);
	SetAnim(4,1,3,1,m_ass[2]);

	m_cur=CScene2D::Create(device, CImport::MAKE_UI_SELECT_CUR, CScene2D::POINT_CENTER);
	m_cur->SetSize(320.f,210.f);
	m_cur->SetPos(SCREEN_WIDTH * 0.3f, CUR_UP);
	SetAnim(4,1,1,1,m_cur);

	m_slotback=CScene2D::Create(device, CImport::MAKE_UI_SELECT_FRAME, CScene2D::POINT_CENTER);
	m_slotback->SetSize(721.f,496.f);
	m_slotback->SetPos(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f + 40.0f);

	// 効果テキスト
	m_message = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_LONG, CScene2D::POINT_CENTER);
	m_message->SetSize(1200.0f,91.0f);
	m_message->SetPos(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9);
	// 効果ウィンドウ
	m_message_win = CScene2D::Create(device, CImport::MAKE_UI_COS_DETAIL, CScene2D::POINT_CENTER,2);
	m_message_win->SetSize(1200.0f,91.0f);
	m_message_win->SetPos(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9);

	// 乗り物名テキスト
	m_veh_mes = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_3, CScene2D::POINT_CENTER);
	m_veh_mes->SetSize(466.0f,91.0f);
	m_veh_mes->SetPos(SCREEN_WIDTH * 0.81f,SCREEN_HEIGHT * 0.55f + 91.0f + 40.0f);
	// 乗り物名ウィンドウ
	m_veh_mes_win = CScene2D::Create(device, CImport::MAKE_UI_ASSY_OPTION, CScene2D::POINT_CENTER,2);
	m_veh_mes_win->SetSize(466.0f,91.0f);
	m_veh_mes_win->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55f + 91.0f + 40.0f);

	// 服装テキスト
	m_cos_mes = CScene2D::Create(device, CImport::MAKE_UI_HYPHEN_3, CScene2D::POINT_CENTER);
	m_cos_mes->SetSize(466.0f,91.0f);
	m_cos_mes->SetPos(SCREEN_WIDTH * 0.81f,SCREEN_HEIGHT * 0.55f + 40.0f);
	// 服装ウィンドウ
	m_cos_mes_win = CScene2D::Create(device, CImport::MAKE_UI_COS_OPTION, CScene2D::POINT_CENTER,2);
	m_cos_mes_win->SetSize(466.0f,91.0f);
	m_cos_mes_win->SetPos(SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.55f + 40.0f);
}

//=============================================================================
// 乗り物の選択
//=============================================================================
void CEquipmentChoice::VehicleChoice()
{
	if(m_cur->GetPos().y==CUR_BUTTOM)
	{
		if(m_keyboard->GetTrigger(DIK_A))
		{
			vehicle_id--;
			if(vehicle_id<=0)
			{
				vehicle_id=0;
			}
			m_player->SetVehicleID((VehicleID)vehicle_id);

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

		}

		else if(m_keyboard->GetTrigger(DIK_D))
		{
			vehicle_id++;
			if(vehicle_id>=VEHICLE_MAX-1)
			{
				vehicle_id=VEHICLE_MAX-1;
			}
			m_player->SetVehicleID((VehicleID)vehicle_id);

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

		}
	}

	// 乗り物によってメッセージの切り替え
	switch(vehicle_id)
	{
	case VEHICLE_TRAM:
		m_veh_mes->SetTex(CImport::MAKE_UI_VEH_TRUM);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_VEH_MES_TRUM);
		break;

	case VHEICLE_DOLLY:
		m_veh_mes->SetTex(CImport::MAKE_UI_VEH_DOLLY);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_VEH_MES_DOLLY);
		break;

	case VHEICLE_LOG:
		m_veh_mes->SetTex(CImport::MAKE_UI_VEH_LOG);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_VEH_MES_LOG);
		break;

	case VEHICLE_BATHTUB:
		m_veh_mes->SetTex(CImport::MAKE_UI_VEH_BATHTUB);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_VEH_MES_BATHTUB);
		break;

	case VEHICLE_SLEIGH:
		m_veh_mes->SetTex(CImport::MAKE_UI_VEH_SLEIGH);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_VEH_MES_SLEIGH);
		break;

	case VHEICLE_TRUCK:
		m_veh_mes->SetTex(CImport::MAKE_UI_VEH_TRUCK);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_HYPHEN_LONG);
		break;

	default:
		m_veh_mes->SetTex(CImport::MAKE_UI_HYPHEN_3);
		if(curUp != true)
			m_message->SetTex(CImport::MAKE_UI_HYPHEN_LONG);
		break;
	}
}
//=============================================================================
// コスチュームの選択
//=============================================================================
void CEquipmentChoice::CostumeChoice()
{
	if(m_cur->GetPos().y==CUR_UP)
	{
		if(m_keyboard->GetTrigger(DIK_A))
		{
			costume_id--;
			if(costume_id<=COSTUME_NONE)
			{
				costume_id=COSTUME_NONE;
			}
			m_player->SetCostumeID((CostumeID)costume_id);

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

		}

		else if(m_keyboard->GetTrigger(DIK_D))
		{
			costume_id++;
			if(costume_id>=COSTUME_MAX-1)
			{
				costume_id=COSTUME_MAX-1;
			}
			m_player->SetCostumeID((CostumeID)costume_id);

			m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

		}
	}

	// コスチュームによってメッセージの切り替え
	switch(costume_id)
	{
		case COSTUME_NONE:
			m_cos_mes->SetTex(CImport::MAKE_UI_COS_NONE);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_HYPHEN_LONG);
			break;
		case COSTUME_KNIGHT:
			m_cos_mes->SetTex(CImport::MAKE_UI_COS_KNIGHT);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_COS_MES_FIGHTER);
			break;
		case COSTUME_SANTA:
			m_cos_mes->SetTex(CImport::MAKE_UI_COS_SANTA);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_COS_MES_SANTA);
			break;
		case COSTUME_SWIMWEAR:
			m_cos_mes->SetTex(CImport::MAKE_UI_COS_SWIM);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_COS_MES_SWIM);
			break;
		case COSTUME_NINJA:
			m_cos_mes->SetTex(CImport::MAKE_UI_COS_NINJA);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_COS_MES_NINJA);
			break;
		case COSTUME_FAITER:
			m_cos_mes->SetTex(CImport::MAKE_UI_COS_FIGHTER);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_COS_MES_FIGHTER);
			break;
		default:
			m_cos_mes->SetTex(CImport::MAKE_UI_HYPHEN_3);
			if(curUp == true)
				m_message->SetTex(CImport::MAKE_UI_HYPHEN_LONG);
			break;
		}
}

//=============================================================================
// アニメーションの更新
//=============================================================================
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
//=============================================================================
// カーソルの更新
//=============================================================================
void CEquipmentChoice::CurUpdate()
{
	if(m_keyboard->GetTrigger(DIK_W))
	{
		m_cur->SetPosY(CUR_UP);
		curUp = true;

		m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

	}

	else if(m_keyboard->GetTrigger(DIK_S))
	{
		m_cur->SetPosY(CUR_BUTTOM);
		curUp = false;

		m_sound->Play( CSound::SOUND_LABEL_SYSTEM_SELECTSE );

	}
}

//=============================================================================
// コスチューム、アッシーの更新
//=============================================================================
void CEquipmentChoice::cosUpdate(int id)
{
	switch (id)
	{
		CImport::TEXTURES texid,assid;
	case 0:
		texid=m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT,-1);
		assid=m_player->ConsultationVehicleTexID(-1);
		if(texid==CImport::TEX_MAX)
		{
			m_cos[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_cos[id]->SetColor(255,255,255,255);
			m_cos[id]->SetTex(texid);
		}

		if(assid==CImport::TEX_MAX)
		{
			m_ass[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_ass[id]->SetColor(255,255,255,255);
			m_ass[id]->SetTex(assid);
		}
		break;

	case 1:
		m_cos[id]->SetTex(m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT));
		m_ass[id]->SetTex(m_player->ConsultationVehicleTexID());
		break;

	case 2:
		texid=m_player->ConsultationPlayerTexID(PLAYER_STATE_WAIT,1);
		assid=m_player->ConsultationVehicleTexID(1);
		if(texid==CImport::TEX_MAX)
		{
			m_cos[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_cos[id]->SetColor(255,255,255,255);
			m_cos[id]->SetTex(texid);
		}

		if(assid==CImport::TEX_MAX)
		{
			m_ass[id]->SetColor(255,255,255,0);
		}
		else
		{
			m_ass[id]->SetColor(255,255,255,255);
			m_ass[id]->SetTex(assid);
		}

		break;
	}
}