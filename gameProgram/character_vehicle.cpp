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
	//アニメーションの更新
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
	if(isDraw)
	{
		//親の描画
		CScene2D::Draw();
	}
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
	if(cntAnim==VEHICLE_ANIMSPD_MOVE*nowAnim)
	{
		if(nowAnim==maxAnim.x)
		{
			isAnimEnd=true;
		}

		else
		{
			nowAnim++;
			SetAnim((int)maxAnim.x,nowAnim,(int)maxAnim.y,RateOfDestruction,this);
		}
	}
	cntAnim++;
		break;
	}

	if(isAnimEnd)
	{
		if(isRupeAnim)
		{
			cntAnim=0;
			nowAnim=1;
			SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
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
		maxAnim.x=VEHICLE_MAXANIM_X_WAIT;
		maxAnim.y=VEHICLE_MAXANIM_Y_WAIT;
		SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
		break;

	case VEHICLE_ANIM_MOVE:
		cntAnim=0;
		nowAnim=1;
		maxAnim.x=VEHICLE_MAXANIM_X_MOVE;
		maxAnim.y=VEHICLE_MAXANIM_Y_MOVE;
		SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
		break;
	}

	AnimMode=AnimID;
	isRupeAnim=Rupe;
}

//=============================================================================
//乗り物の破壊率加算
//=============================================================================
void CVehicle::addRateOfDestruction(int value)
{
	RateOfDestruction+=value;
	//1以下になるのを防ぐ
	if(RateOfDestruction<=1)
	{
		RateOfDestruction=1;
	}
	//コマ最大数以上になるのを防ぐ
	if(RateOfDestruction>=maxAnim.y)
	{
		RateOfDestruction=(int)maxAnim.y;
	}

	SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
}