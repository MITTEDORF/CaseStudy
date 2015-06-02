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

protected:
	void SetVertexPolygon(void);

	bool m_localTex;
	LPDIRECT3DTEXTURE9		m_texture;
	LPDIRECT3DVERTEXBUFFER9	m_vtxBuff;

	float		m_length;		// 対角線の長さ
	float		m_angle;		// 対角線の角度
	POINT_TYPE	m_pointType;	// ポイントの位置
	D3DXVECTOR2	m_coord[4];		// テクスチャコード
};

//=============================================================================
#endif