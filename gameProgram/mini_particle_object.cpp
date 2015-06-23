//*****************************************************************************
//
// パーティクル制御クラス [particle_object.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "particle_manager.h"
#include "import.h"

#include <math.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CMiniParticleObject::CMiniParticleObject(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//変数のNULL埋め
	NullSetVariable();

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMiniParticleObject::Init(LPDIRECT3DDEVICE9 device)
{
	//親の初期化
	CScene2D::Init(device,CImport::PARTICLE_YELLOW_SMALL,POINT_CENTER);
	

	//成功を返す
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CMiniParticleObject::Uninit(void)
{
	//親の終了
	CScene2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CMiniParticleObject::Update(void)
{
	if(isUse)
	{
		ColA-=0.05f;
		m_Rad+=D3DX_PI*0.05f;

		if(m_Rad>D3DX_PI)
		{
			m_Rad-=D3DX_PI*2.0f;
		}

		m_color.a=ColA;
		m_color.r=sinf(m_Rad)+1.5f;
		m_color.g=sinf(m_Rad+(D3DX_PI*0.666f))+1.5f;
		m_color.b=sinf(m_Rad+(D3DX_PI*1.333f))+1.5f;



		Angle+=Anglespd;

		SetColor(m_color);

		SetRot(Angle);
		//座標の再計算
		SetVertexPolygon();

		//親の更新
		CScene2D::Update();

		if(ColA<=0)
		{
			Destroy();
		}
	}
}
//=============================================================================
// 描画
//=============================================================================
void CMiniParticleObject::Draw(void)
{
	if(isUse)
	{
		//親の描画
		CScene2D::Draw();
	}
}
//=============================================================================
// 生成
//=============================================================================
CMiniParticleObject* CMiniParticleObject::Create(LPDIRECT3DDEVICE9 device)
{
	CMiniParticleObject* scene = new CMiniParticleObject;
	scene->Init(device);

	return scene;
}

//=============================================================================
// パーティクル開始処理
//=============================================================================
void CMiniParticleObject::Start(D3DXVECTOR2 pos)
{
		int dsize=2 + (int)( rand() * (5 - 2 + 1.0) / (1.0 + RAND_MAX) );
		SetSize((128.0f*1.5f*0.2f),(128.0f*1.5f*0.2f));

		isUse = true;

		this->SetPos(pos.x,pos.y);

		this->SetTex(CImport::PARTICLE_WHITE_SMALL);

		ColA=1.0f;

		Angle=0.0f;

		Anglespd=(float)(0.01 + (int)( rand() * (0.2 - 0.01 + 1.0)) / (float)(1.0 + RAND_MAX) );


		m_Rad=(float)(0 + (int)( rand() * (D3DX_PI - 0 + 1.0)) / (float)(1.0 + RAND_MAX) );
}

//=============================================================================
// パーティクル破壊処理
//=============================================================================
void CMiniParticleObject::Destroy()
{
	isUse=false;
}