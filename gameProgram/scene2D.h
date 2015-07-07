//*****************************************************************************
//
// CScene2Dクラス [scene2D.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_SCENE_2D_H
#define _MY_SCENE_2D_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "scene.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D : public CScene
{
public:
	typedef enum
	{
		POINT_LEFTTOP,
		POINT_CENTER
	} POINT_TYPE;

	CScene2D(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CScene2D(){};

	static	CScene2D* Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType, int priority = PRIORITY_MAX - 1);
	static	CScene2D* Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void		SetPos(D3DXVECTOR2 pos){m_pos = pos; SetVertexPolygon();}
	void		SetPos(float x, float y){m_pos = D3DXVECTOR2(x, y); SetVertexPolygon();}
	void		SetPosX(float x){m_pos.x = x; SetVertexPolygon();}
	void		SetPosY(float y){m_pos.y = y; SetVertexPolygon();}
	D3DXVECTOR2	GetPos(void){return m_pos;}
	void		SetRot(float rot){m_rot = rot; SetVertexPolygon();}
	float		GetRot(void){return m_rot;}
	void		SetSize(D3DXVECTOR2 size){m_size = size; SetVertexPolygon();}
	void		SetSize(float x, float y){m_size = D3DXVECTOR2(x, y); SetVertexPolygon();}
	D3DXVECTOR2	GetSize(void){return m_size;}
	void		SetColor(D3DXCOLOR color){m_color = color; SetVertexPolygon();}
	void		SetColor(float r, float g, float b, float a){m_color = D3DXCOLOR(r, g, b, a); SetVertexPolygon();}
	D3DXCOLOR	GetColor(void){return m_color;}
	POINT_TYPE	GetPointType(void){return m_pointType;}

	void		SetCord(int n, D3DXVECTOR2 cord){m_coord[n] = cord; SetVertexPolygon();}
	D3DXVECTOR2	GetCord(int n){return m_coord[n];}
	void SetTex(CImport::TEXTURES texture){m_texture = CImport::GetTexture(texture);};

	// 衝突判定
	bool	CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType);
	// 当たり判定サイズセット処理
	void	SetHitSize(D3DXVECTOR2 hitSize){m_hitSize = hitSize;}
	// 当たり判定サイズゲット処理
	D3DXVECTOR2	GetHitSize(void){return m_hitSize;}
	// 当たり判定用座標セット処理
	void	SetHitPos(D3DXVECTOR2 hitPos){m_hitPos = hitPos;}
	// 当たり判定用座標ゲット処理
	D3DXVECTOR2	GetHitPos(void){return (m_hitPos + m_hitOffset);}
	// 当たり判定座標オフセット値セット処理
	void	SetHitOffset(D3DXVECTOR2 offset){m_hitOffset = offset;}
protected:
	void SetVertexPolygon(void);
	void DrawHitBox(void);

	bool m_localTex;
	LPDIRECT3DTEXTURE9		m_texture;
	LPDIRECT3DVERTEXBUFFER9	m_vtxBuff;

	float		m_length;		// 対角線の長さ
	float		m_angle;		// 対角線の角度
	POINT_TYPE	m_pointType;	// ポイントの位置
	D3DXVECTOR2	m_coord[4];		// テクスチャコード

	D3DXVECTOR2	m_hitSize;		// 当たり判定サイズ
	D3DXVECTOR2 m_hitPos;		// 当たり判定用座標
	D3DXVECTOR2	m_hitOffset;	// 当たり判定座標オフセット
	VERTEX_2D	m_hitBox[4];	// 当たり判定ボックス
};

//=============================================================================
#endif