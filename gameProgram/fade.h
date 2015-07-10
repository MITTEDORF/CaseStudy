//*****************************************************************************
//
// CFadeクラス [fade.cpp]
// Author :MAI TANABE |KAZUMA OOIGAWA
//
//*****************************************************************************

#ifndef _MY_FADE_H
#define _MY_FADE_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 構造体定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	LPDIRECT3DTEXTURE9		texture;
	LPDIRECT3DVERTEXBUFFER9	vtxBuff;
	D3DXVECTOR2				size;
	D3DXVECTOR2				pos;
	D3DXVECTOR2				texcoord[4];		// テクスチャコード
}POLYGON_DATA;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADESTATE_NONE = 0,
		FADESTATE_OUT,
		FADESTATE_OUTEND,
		FADESTATE_IN,
		FADESTATE_INEND,
		FADESTATE_MAX
	}FADESTATE;

	CFade(int priority = PRIORITY_MAX - 1, OBJTYPE objtype = OBJTYPE_FADE);
	~CFade(){};

	static	CFade* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void Start(FADESTATE state, int time, float r, float g, float b, float a);

	void	  SetState(FADESTATE state){m_state = state;}
	FADESTATE GetState(void){return m_state;}
	void	  SetTime(int time){m_time = time;}
	int		  GetTime(void){return m_time;}
	void	  SetAlpha(float alpha){m_alpha = alpha;}
	float	  GetAlpha(void){return m_alpha;}
	void	  SetColor(D3DXCOLOR color){m_color = color;}
	D3DXCOLOR GetColor(void){return m_color;}

private:
	FADESTATE	m_state;
	int			m_time;
	float		m_alpha;
	D3DXCOLOR	m_color;
	float		m_cngAlpha;
	bool		m_flg;

};

//=============================================================================
#endif