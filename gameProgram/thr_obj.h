//*****************************************************************************
//
// thr_objクラス [thr_obj.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

#ifndef _THREAD_OBJECT_H
#define _THREAD_OBJECT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CThrObj : public CScene2D
{
public:
	CThrObj( int priority = 0 , OBJTYPE objtype = OBJTYPE_2D);
	~CThrObj(){};
	static		CThrObj* Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos );
	static		CThrObj* Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType , int priority , D3DXVECTOR2 pos );
	HRESULT		Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT		Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);

	void		ThrDraw( void );
	void		ThrUpdate( void );

	  //////////////////////////////////////////
	 //スレッドの外で出来れば触ってほしくない//
	//////////////////////////////////////////

	//{
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
		CThrObj		*GetThrObj( void ){ return m_ThrObj; }
		void		SetThrObj( CThrObj *thr_objpointer ){ m_ThrObj = thr_objpointer; }
	//}
private:
	CThrObj		*m_ThrObj;
};
#endif