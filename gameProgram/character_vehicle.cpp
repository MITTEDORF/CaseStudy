//*****************************************************************************
//
// 乗り物制御クラス [character_vehicle.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_vehicle.h"
#include "vehicle_config.h"

#include "character_player.h"
#include "math_animation.h"

#include "game.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// コンストラクタ
//=============================================================================
CVehicle::CVehicle(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//変数のNULL埋め
	NullSetVariable();

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CVehicle::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture)
{
	//親の初期化
	CScene2D::Init(device,texture,POINT_CENTER);

	//アニメーションの初期化
	SetAnimMode(VEHICLE_ANIM_WAIT,true);

	//成功を返す
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CVehicle::Uninit(void)
{
	//親の終了
	CScene2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CVehicle::Update(void)
{
	UpdateAnim();

	//座標の再計算
	SetVertexPolygon();
	//親の更新
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CVehicle::Draw(void)
{
	//親の描画
	CScene2D::Draw();
}
//=============================================================================
// 生成
//=============================================================================
CVehicle* CVehicle::Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture)
{
	CVehicle* scene = new CVehicle;
	scene->Init(device,texture);

	return scene;
}

//=============================================================================
//アニメーションの更新処理
//=============================================================================
void CVehicle::UpdateAnim()
{
	switch(AnimMode)
	{
	case VEHICLE_ANIM_WAIT:

		break;

	case VEHICLE_ANIM_MOVE:

		break;

	case VEHICLE_ANIM_ATACK:
		
		break;

	case VEHICLE_ANIM_DAMAGE:
		break;
	}

	if(isAnimEnd)
	{
		if(isRupeAnim)
		{
			cntAnim=0;
			nowAnim=1;
			SetAnim(maxAnim,1,this);
		}

		else
		{
			SetAnimMode(VEHICLE_ANIM_WAIT,true);
		}

		isAnimEnd=false;
	}
}
//=============================================================================
//アニメーションのセット処理
//=============================================================================
void CVehicle::SetAnimMode(int AnimID,bool Rupe)
{
	if(AnimMode==AnimID)
	{
		return;
	}

	switch (AnimID)
	{
	case VEHICLE_ANIM_WAIT:
		cntAnim=0;
		nowAnim=1;
		maxAnim=1;
		this->SetTex(CImport::TEX_ASSY_ONE);
		SetAnim(maxAnim,1,this);
		break;

	case VEHICLE_ANIM_MOVE:

		break;

	case VEHICLE_ANIM_ATACK:
		cntAnim=0;
		nowAnim=1;
		maxAnim=5;
		this->SetTex(CImport::TEX_PLAY_ATTACK);
		SetAnim(maxAnim,1,this);
		break;

	case VEHICLE_ANIM_DAMAGE:

		break;
	}

	AnimMode=AnimID;
	isRupeAnim=Rupe;

}

