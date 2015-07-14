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
#include "main.h"
#include "import.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CLIcon
{
public:
	typedef enum
	{
		POINT_LEFTTOP,
		POINT_CENTER
	} POINT_TYPE;

	CLIcon();
	~CLIcon(){};
	static		CLIcon* Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , D3DXVECTOR2 pos );
	static		CLIcon* Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType , D3DXVECTOR2 pos );
	HRESULT		Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT		Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);

	void		SetPos(D3DXVECTOR2 pos){m_pos = pos; SetVertexPolygon();}
	void		SetPos(float x, float y){m_pos = D3DXVECTOR2(x, y); SetVertexPolygon();}
	D3DXVECTOR2	GetPos(void){return m_pos;}
	void		SetRot(float rot){m_rot = rot; SetVertexPolygon();}
	float		GetRot(void){return m_rot;}
	void		SetSize(D3DXVECTOR2 size){m_size = size; SetVertexPolygon();}
	void		SetSize(float x, float y){m_size = D3DXVECTOR2(x, y); SetVertexPolygon();}
	D3DXVECTOR2	GetSize(void){return m_size;}
	void		SetColor(D3DXCOLOR color){m_color = color; SetVertexPolygon();}
	void		SetColor(float r, float g, float b, float a){m_color = D3DXCOLOR(r, g, b, a); SetVertexPolygon();}
	D3DXCOLOR	GetColor(void){return m_color;}
	void SetTex(CImport::TEXTURES texture){m_texture = CImport::GetTexture(texture);};
	static const float POLYGON_SIZE;
	static const int ANIMATION_MAX = 4;
private:
	const char* m_file_path;
	LPDIRECT3DDEVICE9 m_device;
	D3DXVECTOR2 m_pos;
	float m_rot;
	D3DXVECTOR2 m_size;
	D3DXCOLOR m_color;
	void SetVertexPolygon(void);
	POINT_TYPE m_pointType;
	LPDIRECT3DTEXTURE9		m_texture;
	VERTEX_2D m_vtx[4];
	float		m_length;		// 対角線の長さ
	float		m_angle;		// 対角線の角度
	D3DXVECTOR2	m_coord[4];		// テクスチャコード
	bool m_localTex;
	int m_anim_now;
protected:
};
#endif