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
	TYPE_BARRICADE
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
	// 次障害物ポインタセット処理
	void		SetStumNext(CStumbler* next){m_next = next;}
	// 次障害物ポインタゲット処理
	CStumbler*	GetStumNext(void){return m_next;}
	// 前障害物ポインタセット処理
	void		SetStumPrev(CStumbler* prev){m_prev = prev;}
	// 前障害物ポインタゲット処理
	CStumbler*	GetStumPrev(void){return m_prev;}
	// 障害物タイプセット処理
	void		SetStumType(STUM_TYPE type){m_type = type;}
	// デフォルト位置セット処理
	void		SetDefPos(D3DXVECTOR2 pos){m_defpos = pos;}

protected:
	int			m_life;						// 障害物耐久度
	CStumbler*	m_next;						// 次障害物へのポインタ
	CStumbler*	m_prev;						// 前障害物へのポインタ
	STUM_TYPE	m_type;						// 障害物タイプ
	float		m_move;						// 移動値
	D3DXVECTOR2	m_defpos;					// 初期位置
	int			m_texAnim;					// テクスチャアニメーション用タイマ
};

//=============================================================================
#endif