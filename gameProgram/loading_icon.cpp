//*****************************************************************************
//
// loading_iconクラス [loading_icon.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "loading_icon.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// コンストラクタ
//=============================================================================
CLIcon::CLIcon( int priority , OBJTYPE objtype ) : CThrObj(priority, objtype)
{
	update_flag = true;
	draw_flag = false;
}
CLIcon* CLIcon::Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , CScene2D::POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CLIcon* pointer = new CLIcon( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	pointer->SetThrObj( pointer );
	return pointer;

}
CLIcon* CLIcon::Create(LPDIRECT3DDEVICE9 device, const char* texture, CScene2D::POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CLIcon* pointer = new CLIcon( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	pointer->SetThrObj( pointer );
	return pointer;

}
HRESULT CLIcon::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, CScene2D::POINT_TYPE pointType)
{
	CThrObj::Init( device , texture , pointType );
	return S_OK;

}
HRESULT CLIcon::Init(LPDIRECT3DDEVICE9 device, const char* texture, CScene2D::POINT_TYPE pointType)
{
	CThrObj::Init( device , texture , pointType );
	return S_OK;
}
void CLIcon::Uninit(void)
{
	CThrObj::Uninit();
}
void CLIcon::Update(void)
{
		float rot = CThrObj::GetRot();
		rot+=0.001f;
		CThrObj::SetRot(rot);
		CThrObj::ThrUpdate();
}
void CLIcon::Draw(void)
{
		CThrObj::ThrDraw();
}
