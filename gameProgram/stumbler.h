//*****************************************************************************
//
// stumblerクラス [stumbler.h]
// Author : KEN MATSUURA
//
//*****************************************************************************

#ifndef _STUMBLER_H
#define _STUMBLER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CStumbler : public CScene2D
{
public:
	CStumbler(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CStumbler(){};

	static	CStumbler* Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);

	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}
	void	Attack(int damage){m_life -= damage;}
	bool	LivingCheck(void);
	bool	CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pType);

protected:
	int		m_life;							// 障害物耐久度
};

//=============================================================================
#endif