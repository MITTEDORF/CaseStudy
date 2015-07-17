//*****************************************************************************
//
// プレイヤー制御クラス [character_player.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_goal.h"

#include "import.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 実体定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacterGoal::Init(LPDIRECT3DDEVICE9 device)
{
	
	CharacterL=CScene2D::Create(device,CImport::GOAL_CHAR_RIGHT,CScene2D::POINT_CENTER);
	CharacterL->SetPos(0.0f-534.0f/4.0f,SCREEN_HEIGHT-128.0f-544.0f/8.0f);
	CharacterL->SetSize(534.0f/2.0f,544.0f/2.0f);

	CharacterR=CScene2D::Create(device,CImport::GOAL_CHAR_LEFT,CScene2D::POINT_CENTER);
	CharacterR->SetPos(SCREEN_WIDTH+576.0f/4.0f,SCREEN_HEIGHT-128.0f-522.0f/8.0f);
	CharacterR->SetSize(576.0f/2.0f,522.0f/2.0f);



	//成功を返す
	return S_OK;
}

void CCharacterGoal::Start(CScene* Target)
{
	if(!isStart)
	{
		if(Target)
		{
			target=Target;
			lenL = (target->GetPos().x-CharacterL->GetPos().x-534.0f/3.0f)/80.0f;
			lenR = (target->GetPos().x-CharacterR->GetPos().x+576.0f/2.0f)/80.0f;
		}

		else
		{
			lenL = (SCREEN_WIDTH/2.0f-CharacterL->GetPos().x-534.0f/3.0f)/80.0f;
			lenR = (SCREEN_WIDTH/2.0f-CharacterR->GetPos().x+576.0f/3.0f)/80.0f;
		}

		isStart=true;
	}
}

//=============================================================================
// クリエイト
//=============================================================================
CCharacterGoal* CCharacterGoal::Create(LPDIRECT3DDEVICE9 device)
{
	CCharacterGoal* scene = new CCharacterGoal();
	//初期化
	scene->Init(device);

	return scene;
}
//=============================================================================
// 終了
//=============================================================================
void CCharacterGoal::Uninit(void)
{

	//親の終了
	CScene2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CCharacterGoal::Update(void)
{
	if(isStart)
	{
		if(Cunt>=80)
		{
			isFade=true;
			return;
		}

		CharacterR->SetPosX(CharacterR->GetPos().x+lenR);
		CharacterL->SetPosX(CharacterL->GetPos().x+lenL);
		Cunt++;
	}
	//親の更新
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CCharacterGoal::Draw(void)
{
	
}