//*****************************************************************************
//
// loading_iconクラス [loading_icon.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

#ifndef _LOADING_ICON_H
#define _LOADING_ICON_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "thr_obj.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CLIcon : public CThrObj
{
public:
	CLIcon( int priority = 0 , OBJTYPE objtype = OBJTYPE_2D);
	~CLIcon(){};
	static		CLIcon* Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , CScene2D::POINT_TYPE pointType , int priority , D3DXVECTOR2 pos );
	static		CLIcon* Create(LPDIRECT3DDEVICE9 device, const char* texture, CScene2D::POINT_TYPE pointType , int priority , D3DXVECTOR2 pos );
	HRESULT		Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, CScene2D::POINT_TYPE pointType);
	HRESULT		Init(LPDIRECT3DDEVICE9 device, const char* texture, CScene2D::POINT_TYPE pointType);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);

private:
	bool draw_flag;
	bool update_flag;
protected:
};
#endif