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
// 構造体
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 画像データ識別
typedef enum{
	TYPE_SIGNBOARD = 0,
	TYPE_LION,
	TYPE_ROCK,
	TYPE_LOG_LEFT,
	TYPE_LOG_CENTER,
	TYPE_LOG_RIGHT,
	TYPE_BIRD,
	TYPE_DUSTBOX,
	TYPE_BARRICADE,
	TYPE_MAX
}STUM_TYPE;

// 障害物情報
typedef struct{
	STUM_TYPE type;
	D3DXVECTOR2 Index;
}STUM_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CStumbler : public CScene2D
{
public:
	CStumbler(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CStumbler(){};

	static	CStumbler* Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType);

	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	// スクロール処理
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}
	// HPセット処理
	void	SetHP(int life){m_life = life;}
	// HPゲット処理
	int		GetHP(void){return m_life;}
	// 攻撃を受けた場合のHP減算処理
	void	Attack(int damage){m_life -= damage;}
	// 生存チェック
	bool	LivingCheck(void);
	// 衝突判定
	bool	CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pType);

protected:
	int		m_life;							// 障害物耐久度
};

//=============================================================================
#endif