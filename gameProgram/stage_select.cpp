//*****************************************************************************
//
// ステージ選択画面制御クラス [stage_selrect.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stage_select.h"
#include "manager.h"
#include "fade.h"

#include "game.h"

#include "inputKeyboard.h"

#include "character_player.h"

#include "equipment_choice.h"

#include "math_animation.h"

#include "equipment_choice_config.h"
#include "character_config.h"

#include "stage_select_conf.h"

#include "debugproc.h"

#include "configholder.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStageSelect::Init(LPDIRECT3DDEVICE9 device)
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
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CStageSelect::Uninit(void)
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
void CStageSelect::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{

		SelectObjectUpdate();

		ObjectUpdate();

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
		CConfigHolder::Set(CONFIG_STAGE,nowSelectObject);
		CManager::SetNextPhase((CPhase*)new CEquipmentChoice);
	}
}

//=============================================================================
// 描画
//=============================================================================
void CStageSelect::Draw(void)
{

}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CStageSelect::InitObject(LPDIRECT3DDEVICE9 device)
{
	//背景の生成
	select_bg = CScene2D::Create(device, CImport::STAGE_SELECT_BG, CScene2D::POINT_LEFTTOP, 1);
	select_bg ->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	select_bg ->SetPos(0.0f, 0.0f);

	mesPol = CScene2D::Create(device, CImport::STAGE_SELECT_MESSAGE, CScene2D::POINT_CENTER, 1);
	mesPol->SetSize(951.0f, 81.0f);
	mesPol->SetPos(SCREEN_WIDTH/2, 50.0f);

	select_object[STAGE_DESERT]    =CScene2D::Create(device, CImport::STAGE_SELECT_DESERT, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_FOREST]    =CScene2D::Create(device, CImport::STAGE_SELECT_FOREST, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_GLACIER]   =CScene2D::Create(device, CImport::STAGE_SELECT_GLACIER, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_SAVANNAH]  =CScene2D::Create(device, CImport::STAGE_SELECT_SAVANNAH, CScene2D::POINT_CENTER, 1);
	select_object[STAGE_WATERSIDE] =CScene2D::Create(device, CImport::STAGE_SELECT_WATERSIDE, CScene2D::POINT_CENTER, 1);

	for(int i=0;i<STAGE_MAX;i++)
	{
		select_object[i] ->SetSize(POL_SIZE[i]);
		select_object[i] ->SetPos(POL_POS[i]);
	}

	select_object[nowSelectObject]->SetSize(POL_SIZE[STAGE_FOREST]*1.2f);
	select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 20.0f);
}

//=============================================================================
// オブジェクトの選択更新
//=============================================================================
void CStageSelect::SelectObjectUpdate()
{
	if(m_keyboard->GetTrigger(DIK_D))
	{
		m_time=0;
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
		select_object[nowSelectObject] ->SetPos(POL_POS[nowSelectObject]);
		select_object[nowSelectObject]->SetRot(0);
		nowSelectObject++;
		if(nowSelectObject>=STAGE_MAX){nowSelectObject=0;}
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
		if(nowSelectObject == STAGE_GLACIER || nowSelectObject == STAGE_SAVANNAH)
			select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y + 10.0f);
		else
			select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 10.0f);
	}

	if(m_keyboard->GetTrigger(DIK_A))
	{
		m_time=0;
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]);
		select_object[nowSelectObject] ->SetPos(POL_POS[nowSelectObject]);
		select_object[nowSelectObject]->SetRot(0);
		nowSelectObject--;
		if(nowSelectObject<=-1){nowSelectObject=STAGE_MAX-1;}
		select_object[nowSelectObject]->SetSize(POL_SIZE[nowSelectObject]*1.2f);
		if(nowSelectObject == STAGE_GLACIER || nowSelectObject == STAGE_SAVANNAH)
			select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y + 13.0f);
		else
			select_object[nowSelectObject] ->SetPosY(select_object[nowSelectObject]->GetPos().y - 13.0f);
	}
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CStageSelect::ObjectUpdate()
{
	//揺れ時間を増やす
	m_time += SHAKING_SPD;
	//sinを使ってrot値検出
	float value = sinf(m_time) * SHAKING_WIDTH;
	//揺らす
	select_object[nowSelectObject]->SetRot(value);
}